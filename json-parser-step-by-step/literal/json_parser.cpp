#include "common.h"
 
class RJson {
public:
	RJson(const string& json_text);
	PARSE_CODE parseJson();
private:
	PARSE_CODE parseValue(json_value* v); // 解析 value 
	PARSE_CODE parseLiteral(json_value* v, const string& literal, json_type type); // 解析 false, true和 null三个字面值 
	
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

int main()
{
	// read json text from file.
	string json_text = getJsonFromFile("false.json");
	//string json_text = getJsonFromFile("true.json");
	//string json_text = getJsonFromFile("null.json");
	RJson json_parser(json_text);
	PARSE_CODE code = json_parser.parseJson();

	if (code == PARSE_OK)
		cout << "parse ok.\n";
	else
		cout << "parse error.\n";
}
