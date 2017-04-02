#ifndef RSTRING_H
#define RSTRING_H

#include <utility>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;

class RString {
	friend std::ostream& operator<<(std::ostream& os, const RString& rhs);
	friend std::istream& operator>>(std::istream& is, const RString& rhs);
public:
	using size_type = unsigned int;
	using iterator = char *;
	RString();
	// Copy constructor. Constructs the string with the copy of the contents of other.
	RString(const RString& other);
	// Move constructor. Constructs the string with the contents of other using move semantics.
	// other is left in valid, but unspecified state.
	RString(RString&& other);
	RString(const RString& other, size_type pos, size_type count);
	RString(const RString& other, size_type pos);
	RString(const char* s);
	RString(const char* s, size_type);
	RString(size_type count, char ch);
	RString(iterator first, iterator last);
	RString(std::initializer_list<const char*> init);
	RString& operator=(const RString& str);
	RString& operator=(RString&& str);
	char& operator[](size_type pos) { return data[pos]; }
	const char& operator[](size_type pos) const { return std::move(data[pos]); }
	~RString() noexcept;
public:
	char front() { return data[0]; }
	const char front() const { return data[0]; }
	char back() { return data[strlen(data)-1]; }
	const char back() const { return data[strlen(data)-1]; }
	bool empty() const { return size() == 0; }
	size_type size() const { return strlen(data); }
	size_type length() const { return strlen(data); }
	const char* c_str() const { return data; }
public:
	static const size_type npos = -1;
private:
	void swap(RString& rhs) { std::swap(data, rhs.data); }
private:
	char* data;
};

RString::RString(): data(new char[1])
{
	*data = '\0';
}

RString::RString(const RString& rhs):
	data(new char[rhs.size()+1])
{
	strcpy(data, rhs.data);
	data[rhs.size()+1] = '\0';
}

RString::RString(RString&& rhs):
	data(rhs.data)
{
	rhs.data = nullptr;
}

RString::RString(const RString& rhs, size_type pos, size_type count)
{
	if(pos >= rhs.length())
		throw std::out_of_range("RString::RString(const RString& rhs, size_type pos, size_type count); pos error");
	count = (count + pos > rhs.length() ? (rhs.length()-pos) : count);
	data = new char(count+1);
	strncpy(data, rhs.data+pos, count);
	data[count] = '\0';
}

RString::RString(const RString& rhs, size_type pos):
	RString(rhs, pos, rhs.size()) // delegating constructor
{
}

RString::RString(const char* s):
	data(new char[strlen(s)+1])
{
	strcpy(data, s);
	data[strlen(s)] = '\0';
}

RString::RString(const char* s, size_type count)
{
	if (count > strlen(s))
		throw std::out_of_range("count is bigger than string's size");
	data = new char(count+1);
	strncpy(data, s, count);
	data[count] = '\0';
}

RString::RString(size_type count, char ch):
	data(new char(count+1))
{
	for (int i = 0; i < count; ++i) data[i] = ch;
	data[count] = '\0';
}

RString& RString::operator=(const RString& rhs)
{
	RString tmp(rhs);
	swap(tmp);
	return *this;
}

RString& RString::operator=(RString&& rhs)
{
	swap(rhs);
	return *this;
}

RString::~RString() noexcept
{
	delete [] data;
}

std::ostream& operator<<(std::ostream& os, const RString& rhs)
{
	int sz = rhs.size();
	for (int i = 0; i < sz; ++i)
		os << rhs.data[i];
	return os;
}

std::istream& operator>>(std::istream& is, const RString& rhs)
{
	int sz = rhs.size();
	for (int i = 0; i < sz; ++i)
		is >> rhs.data[i];
	return is;
}

#endif
