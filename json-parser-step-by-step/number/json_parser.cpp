#include "common.h"
 
class RJson {
public:
	RJson(const string& json_text);
	PARSE_CODE parseJson();
private:
	PARSE_CODE parseValue(json_value* v); // ���� value 
	PARSE_CODE parseLiteral(json_value* v, const string& literal, json_type type); // ���� false, true�� null��������ֵ 
	PARSE_CODE parseNumber(json_value* v);
	void cleanWhitespace() { while (isspace(*json)) ++json; } // ����ո� 
	void eatChar(char ch) { assert(*json == ch); ++json; } // �ö���ȷ�� json ָ����ַ��������������ַ�һ�� 
private:
	const char* json; // ��ָ�����JSON�ı� 
	json_value v; // ����JSON�ṹ 
};

// ��ʼ��
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
	if (*p == '-') // �������� 
		++p;

	if (*p == '0') { // �����0��ͷ���������﷨ͼ��С����ʾΪ 0.xxx�������� 0123.xxx 
		++p;
	} else { // ������������ 
		if (!isdigit(*p))
			return PARSE_INVALID_VALUE; // ���������֣�����Чֵ 
		while (isdigit(*p))
			++p;
	}
	
	if (*p == '.') { // ����С�� 
		++p;
		if (!isdigit(*p))
			return PARSE_INVALID_VALUE;
		while (isdigit(*p))
			++p;
	}

	if (*p == 'e' || *p == 'E') { // ������ѧ��������ʽ������ 
		++p;
		if (*p == '+' || *p == '-')
			++p;
		if (!isdigit(*p)) return PARSE_INVALID_VALUE;
		while (isdigit(*p)) ++p;
	}

	errno = 0;
	double d = std::strtod(json, NULL); // ���ַ�����ʽ����ת��Ϊdouble����
	// �������̫��ȫ�ֱ���errno ������Ϊ ERANGE��strtod ����Ϊ HUGE_VAL �� -HUGE_VAL������̫�����̫С 
	if ((errno == ERANGE) || (d == HUGE_VAL) || (d == -HUGE_VAL))
		return PARSE_NUMBER_TOO_BIG;
	v->num = d;
	v->type = RJSON_NUMBER; // ����Ϊ�������� 
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
