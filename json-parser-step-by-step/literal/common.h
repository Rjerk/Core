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
    PARSE_OK, // 解析成功
    PARSE_INVALID_VALUE, // 无效的值
    PARSE_NOT_SINGULAR_VALUE, // 不是一个对象或者一个数组
	PARSE_NUMBER_TOO_BIG, // 数字太大
	PARSE_INVALID_ESCAPE_CHARCTER, // 无效的转义字符
	PARSE_INVALID_UNICODE_HEX, // 无效的 UNICODE
	PARSE_MISS_QUOTATION_MARK, // 缺少引号
	PARSE_INVALID_STRING_CHAR, // string 里有无效的字符
	PARSE_INVALID_UNICODE_SURROGATE, // 无效的UNICODE代理
	PARSE_MISS_KEY, // object缺少键
	PARSE_MISS_COLON, // object缺少冒号
	PARSE_MISS_COMMA_OR_CURLY_BRACKET, // object缺少逗号或括号
	PARSE_MISS_COMMA_OR_SQUARE_BRACKET // array里缺少逗号或括号
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
    json_type type; // 类型
    union {
        double num; // number
        struct {
            char* s; // 保存string
            size_t len; // string长度
        };
        struct {
            json_pair_t* pair; // object 的 string/value 对
            size_t objSize; // object 的大小
        };
        struct {
            json_value* elem; // array 的大小
            size_t arrSize; // array 大小
        };
    };
};

struct json_pair {
	char* str; // string
	size_t len; // string 长度
	json_value_t value; // value
};

#endif
