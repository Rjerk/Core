#include "common.h"
 
class RJson {
public:
	RJson(const string& json_text);
	PARSE_CODE parseJson();
private:
	PARSE_CODE parseValue(json_value* v); // 解析 value 
	PARSE_CODE parseLiteral(json_value* v, const string& literal, json_type type); // 解析 false, true和 null三个字面值 
	PARSE_CODE parseNumber(json_value* v);
	void cleanWhitespace() { while (isspace(*json)) ++json; } // 清除空格 
	void eatChar(char ch) { assert(*json == ch); ++json; } // 用断言确保 json 指向的字符和我们期望的字符一样 
private:
	const char* json; // 用指针遍历JSON文本 
	json_value v; // 保存JSON结构 
};

// 初始化
RJson::RJson(const string& json_text)
{
	json = const_cast<char*>(json_text.data());
	v.type = RJSON_NULL;
}

PARSE_CODE RJson::parseJson()
{
	cleanWhitespace();
	PARSE_CODE code;
	if ((code = parseValue(&v)) == PARSE_OK) {
		if (*json != '\0')
			code = PARSE_INVALID_VALUE;
	}
	return code;
}

PARSE_CODE RJson::parseValue(json_value* v)
{
	switch (*json) {
		case 't': return parseLiteral(v, "true", RJSON_TRUE);
		case 'f': return parseLiteral(v, "false", RJSON_FALSE);
		case 'n': return parseLiteral(v, "null", RJSON_NULL);
		default: return parseNumber(v); 
	}
	return PARSE_INVALID_VALUE;
}

PARSE_CODE RJson::parseLiteral(json_value* v, const string& literal, json_type type)
{
	eatChar(literal[0]);
	size_t i = 0;
	for (; literal[i+1]; ++i) {
		if (json[i] != literal[i+1])
			return PARSE_INVALID_VALUE;
	}
	json += i;
	v->type = type;
	return PARSE_OK;
}

PARSE_CODE RJson::parseNumber(json_value* v)
{
	const char* p = json;
	if (*p == '-') // 跳过负号 
		++p;

	if (*p == '0') { // 如果以0开头，跳过；语法图中小数表示为 0.xxx，不会是 0123.xxx 
		++p;
	} else { // 跳过所有数字 
		if (!isdigit(*p))
			return PARSE_INVALID_VALUE; // 碰见非数字，则无效值 
		while (isdigit(*p))
			++p;
	}
	
	if (*p == '.') { // 解析小数 
		++p;
		if (!isdigit(*p))
			return PARSE_INVALID_VALUE;
		while (isdigit(*p))
			++p;
	}

	if (*p == 'e' || *p == 'E') { // 解析科学计数法形式的数字 
		++p;
		if (*p == '+' || *p == '-')
			++p;
		if (!isdigit(*p)) return PARSE_INVALID_VALUE;
		while (isdigit(*p)) ++p;
	}

	errno = 0;
	double d = std::strtod(json, NULL); // 将字符串形式数字转换为double类型
	// 如果数字太大，全局变量errno 被设置为 ERANGE，strtod 设置为 HUGE_VAL 或 -HUGE_VAL，正数太大或负数太小 
	if ((errno == ERANGE) || (d == HUGE_VAL) || (d == -HUGE_VAL))
		return PARSE_NUMBER_TOO_BIG;
	v->num = d;
	v->type = RJSON_NUMBER; // 设置为数字类型 
	json = p;
	return PARSE_OK;
}

int main()
{
	// read json text from file.
	string json_text = getJsonFromFile("valid_number.json");
	// string json_text = getJsonFromFile("invalid_number.json");
	RJson json_parser(json_text);
	PARSE_CODE code = json_parser.parseJson();

	if (code == PARSE_OK)
		cout << "parse ok.\n";
	else
		cout << "parse error.\n";
}
