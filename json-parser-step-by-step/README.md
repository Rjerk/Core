# 动手写一个 JSON Parser

## JSON 是什么？

JSON 是一种基于文本、容易读写、轻量级的数据交换格式。什么是格式？可以理解为语法。

JSON 用于数据存储，包含了所需要的数据集合。在人机都需要识别和交换数据时，可以用 JSON 作为配置文件，包含 IP 地址、端口号，目录：

```
{
    "ip": "127.0.0.1",
    "port": "8000",
    "docroot": "/var/www/"
}
```

在一些非关系型数据库中常使用 JSON 作为数据存储，如：

```
{
    "firstName": "John",
    "lastName": "Smith",
    "sex": "male",
    "age": 25,
    "address": {
        "streetAddress": "21 2nd Street",
        "city": "New York",
        "state": "NY",
        "postalCode": "10021"
    },
    "phoneNumber": [
        { "type": "home", "number": "212 555-1234" },
        { "type": "fax", "number": "646 555-4567" }
    ]
}
```

可以看到，JSON 可读性良好，十分书写简单。

## JSON 的格式

当我们阅读英文时，"I eat two apples"，我们分析句子基本结构，然后提取信息，如主语 I，谓语 ear，宾语 two balls.

解析 JSON 也是类似的。当我们的应用需要从 JSON 格式的文件（以.json为后缀的文件）中读取数据时，首先需要解析它，即对它的内容进行语法分析，确保语法结构是正确的，然后从中提取我们需要的数据。

JSON 基于两种结构：
- object 对象，一种无序的 string/value 对的集合
- array  数组，一种有序的值的集合

### object

object 一个对象以 { 作为开始，} 作为结束，里面的元素为0或多个以逗号分隔的 string:value 对。它的语法图如下：

![](http://json.org/object.gif)

string 为字符串，用双引号为边界，里面为0或多个字符，字符可以是 UNICODE 字符，转移字符(以反斜杠转义)。

就像 C语言里的字符串。它的语法图为：

![](http://json.org/string.gif)

比如：
```
""
"abc"
"\"123\t\b"
"\u8964"
```

value 是 string 对应的值，它可以为 string, number, object, array, 以及三个字面值 true, false, null 之一。

![](http://json.org/value.gif)

number 是普通的数字，可以为带符号的整数，小数，也可以用科学计数法的形式。

比如：
```
-0.15e1
10.6E+2
```  

![](http://json.org/number.gif)

### array

array 是0或多个以逗号分隔的 value 的集合。语法图为：

![](http://json.org/array.gif)

比如：
```
["abc", 123, false, ["ccc"]]
[{ "123": 123 }, "456"]
```

### JSON 的解析

下面从自己写的项目[rjson-parser](https://github.com/Rjerk/rjson-parser/)里并提取代码片段作为示例，并附加测试运行保证解析成功。

#### 辅助结构体和函数

用PARSE_CODE保存每次解析后的结果.

```
enum PARSE_CODE {
    PARSE_OK, // 解析成功
    ...
};
```

用 json_value 结构体保存 value。使用 union 保存 number, string, object, array 其中一个类型。

```
struct json_value {
    json_type type; // 类型
    ...
};
```

值的类型 json_type

```
enum json_type {
    RJSON_STRING, // string
    RJSON_NUMBER, // number
    ...
};
```

object 里的 string/value 对：json_pair

```
struct json_pair {
	char* str; // string
	size_t len; // string 长度
	json_value_t value; // value
};
```

#### 字面值的解析

此节可运行的完整代码在：[这里](https://github.com/Rjerk/snippets/tree/master/json-parser-step-by-step/literal)

解析 true, false, null 这三个字面值。

```
PARSE_CODE RJson::parseValue(json_value* v)
{
	switch (*json) {
		case 't': return parseLiteral(v, "true", RJSON_TRUE);
		case 'f': return parseLiteral(v, "false", RJSON_FALSE);
		case 'n': return parseLiteral(v, "null", RJSON_NULL);
	}
	return PARSE_INVALID_VALUE;
}
```

将三个字面值和得到的JSON文本指针逐个进行比较。

```
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
```

#### 数字的解析

此节可运行的完整代码在：[这里](https://github.com/Rjerk/snippets/tree/master/json-parser-step-by-step/number)

按照语法图的顺序来解析数字，像 -0123.1 这样的数字是无效的（0后面应该为小数点），-0.5E+2 这样的是有效的。

```
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
```

#### 字符串的解析

Undo.