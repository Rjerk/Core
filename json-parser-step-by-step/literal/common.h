#ifndef COMMON_H
#define COMMON_H

#include <fstream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <cassert>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;

using json_value_t = struct json_value;
using json_pair_t = struct json_pair;

string getJsonFromFile(const string& filename)
{
	std::ifstream t(filename);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

enum PARSE_CODE {
    PARSE_OK, // �����ɹ�
    PARSE_INVALID_VALUE, // ��Ч��ֵ
    PARSE_NOT_SINGULAR_VALUE, // ����һ���������һ������
	PARSE_NUMBER_TOO_BIG, // ����̫��
	PARSE_INVALID_ESCAPE_CHARCTER, // ��Ч��ת���ַ�
	PARSE_INVALID_UNICODE_HEX, // ��Ч�� UNICODE
	PARSE_MISS_QUOTATION_MARK, // ȱ������
	PARSE_INVALID_STRING_CHAR, // string ������Ч���ַ�
	PARSE_INVALID_UNICODE_SURROGATE, // ��Ч��UNICODE����
	PARSE_MISS_KEY, // objectȱ�ټ�
	PARSE_MISS_COLON, // objectȱ��ð��
	PARSE_MISS_COMMA_OR_CURLY_BRACKET, // objectȱ�ٶ��Ż�����
	PARSE_MISS_COMMA_OR_SQUARE_BRACKET // array��ȱ�ٶ��Ż�����
};

enum json_type {
    RJSON_STRING, // string
    RJSON_NUMBER, // number
    RJSON_OBJECT, // object
    RJSON_ARRAY, // array
    RJSON_FALSE, // false
    RJSON_TRUE, // true
    RJSON_NULL // null
};

struct json_value {
    json_type type; // ����
    union {
        double num; // number
        struct {
            char* s; // ����string
            size_t len; // string����
        };
        struct {
            json_pair_t* pair; // object �� string/value ��
            size_t objSize; // object �Ĵ�С
        };
        struct {
            json_value* elem; // array �Ĵ�С
            size_t arrSize; // array ��С
        };
    };
};

struct json_pair {
	char* str; // string
	size_t len; // string ����
	json_value_t value; // value
};

#endif
