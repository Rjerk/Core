#ifndef STRING_H
#define STRING_H

#include <utility>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;

using size_type = std::uint32_t;
using iterator = char *;

class String {
	// Non-member functions
	friend String operator+(const String& lhs, const String& rhs);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	// Input/output
	friend std::ostream& operator<<(std::ostream& os, const String& rhs);
	friend std::istream& operator>>(std::istream& is, String& rhs);
	friend std::istream& getline(std::istream& is, String& rhs);
public:
	// Constructor
	String();
	String(const String& other);
	String(String&& other);
	String(const String& other, size_type pos, size_type count);
	String(const String& other, size_type pos);
	String(const char* s);
	String(const char* s, size_type);
	String(size_type count, char ch);
	String(iterator first, iterator last);
	String(std::initializer_list<char> init);
	// Destructor
	~String() noexcept;
	String& operator=(String str);
	String& operator=(const char* s);
	String& operator=(char ch);
	// assign
	String& assign(size_type count, char ch);
	String& assign(const String& str);
	String& assign(const String& str, size_type pos, size_type count);
	String& assign(String&& str) noexcept;
	String& assign(const char* s, size_type count);
	String& assign(const char* s);
public:
	// Element access
	char& at(size_type pos) { if (pos > size()) throw std::out_of_range("String::at"); return data_[pos]; }
	const char& at(size_type pos) const { if (pos > size()) throw std::out_of_range("String::at"); return static_cast<const char&>(data_[pos]); }
	char& operator[](size_type pos) { return data_[pos]; }
	const char& operator[](size_type pos) const { return std::move(data_[pos]); }
	char front() { return data_[0]; }
	const char front() const { return data_[0]; }
	char back() { return data_[size_-1]; }
	const char back() const { return data_[size_-1]; }
	const char* data() const { return static_cast<const char*>(data_); }
	char* data() { return data_;}
	const char* c_str() const { return static_cast<const char*>(data_); }
	// Iterators
	iterator begin() noexcept;
	iterator end() noexcept;
	// Capacity
	bool empty() const { return size_ == 0; }
	size_type size() const { return size_; }
	size_type length() const { return size_; }
	size_type max_size() const { return maxsize_; }
	void reserve(size_type new_cap = 0);
	size_type capacity() const { return capacity_; }
	void shrink_to_fit();
	// Operations
	void clear();
	String& insert(size_type index, size_type count, char ch);
	String& append(size_type count, char ch);
	String& append(const String& str);
	String& append(const String& str, size_type pos, size_type count);
	String& append(const char* s, size_type count);
	String& append(const char* s);
	String& operator+=(const String& rhs);
	String& operator+=(char c);
	String& operator+=(const char* s);
	int compare(const String& rhs) const;
	int compare(const char* s) const;
	void resize(size_type count);
	void resize(size_type count, char ch);
	void swap(String& rhs) noexcept;
	// Search
	size_type find(const String& str, size_type pos = 0 ) const;
public:
	// Constants
	static const size_type npos = -1;
private:
	void reallocate(size_type size);
private:
	size_type size_;
	size_type capacity_;
	char* data_;
	static const size_type maxsize_ = static_cast<size_type>(-1) / sizeof(char) - 1;
};

// Constructor
String::String():
	data_(NULL), size_(0), capacity_(0)
{
}

String::String(const String& rhs):
	size_(rhs.size_), capacity_(rhs.capacity_), data_(new char[capacity_])
{
	memcpy(data_, rhs.data_, size_);
}

String::String(String&& rhs):
	size_(rhs.size_), capacity_(rhs.capacity_), data_(rhs.data_)
{
	rhs.data_ = nullptr;
}

String::String(const String& rhs, size_type pos, size_type count)
{
	if(pos >= rhs.length())
		throw std::out_of_range("String::String");
	size_ = (count + pos > rhs.length() ? (rhs.length()-pos) : count);
	capacity_ = size_;
	data_ = new char[capacity_];
	strncpy(data_, rhs.data_+pos, size_);
}

String::String(const String& rhs, size_type pos):
	String(rhs, pos, rhs.size()) // delegating constructor
{
}

String::String(const char* s):
	size_(strlen(s)), capacity_(size_), data_(new char[capacity_])
{
	strcpy(data_, s);
}

String::String(const char* s, size_type count)
{
	if (count > strlen(s))
		throw std::out_of_range("String::String");
	size_ = count;
	capacity_ = size_;
	data_ = new char[capacity_];
	memcpy(data_, s, capacity_);
}

String::String(size_type count, char ch):
	size_(count), capacity_(size_), data_(new char[capacity_])
{
	memset(data_, ch, capacity_);
}

String::String(iterator first, iterator last):
	size_(last-first), capacity_(size_), data_(new char[capacity_])
{
	memcpy(data_, first, capacity_);
}

String::String(std::initializer_list<char> init):
	size_(init.size()), capacity_(size_), data_(new char[capacity_])
{
	size_type i = 0;
	for (auto c : init)
		data_[i++] = c;
}

// Destructor
String::~String() noexcept
{
	delete [] data_;
}

String& String::operator=(String rhs)
{
	this->swap(rhs);
	return *this;
}

String& String::operator=(const char* s)
{
	
}

String& String::operator=(char ch)
{
	
}

// assign
String& String::assign(size_type count, char ch)
{
	if (count > maxsize_)
		throw std::length_error("String::assign");
	if (count > capacity_)
		reallocate(count);
	memset(data_, ch, count);
	return *this;
}

String& String::assign(const String& str)
{
	return this->assign(str, 0, str.size_);
}

String& String::assign(const String& str, size_type pos, size_type count)
{
	if (pos > str.size_)
		throw std::out_of_range("String::assign");
	if (pos + count > maxsize_)
		throw std::length_error("String::assign");
	count = (pos + count > str.size_ ? (str.size_ - pos) : count);
	if (count > size_)
		reallocate(count);
	memcpy(data_, str.data_+pos, count);
	return *this;
}

String& String::assign(String&& str) noexcept
{
	this->swap(str);
	str.data_ = nullptr;
	return *this;
}

String& String::assign(const char* s, size_type count)
{
	count = (count > strlen(s) ? strlen(s) : count);
	cout << count << endl;
	cout << capacity_ << endl;
	if (count > capacity_)
		reallocate(count);
	memcpy(data_, s, count);
	return *this;
}

String& String::assign(const char* s)
{
	return this->assign(s, strlen(s));
}

// Iterators
iterator String::begin() noexcept
{
	return data_;
}

iterator String::end() noexcept
{
	return data_ + size_;
}

// Capacity
void String::reserve(size_type new_cap)
{
	if (new_cap > maxsize_)
		throw std::length_error("String::reserve");
	if (new_cap <= capacity_ || new_cap <= size_)
		return ;
	char* tmp = new char[size_];
	memcpy(tmp, data_, size_);
	delete [] data_;
	data_ = tmp;
	tmp = nullptr;
	capacity_ *= 2; // if new_cap > capacity_, capacity *= 2.
}

void String::shrink_to_fit()
{
	if (size_ < capacity_)
		reallocate(size_);
}

// Operation
void String::clear()
{
	memset(data_, char(), size_);
	size_ = 0;
}

String& String::insert(size_type index, size_type count, char ch)
{
	if (index > size_)
		throw std::out_of_range("String::insert");
	if (size_+count > maxsize_)
		throw std::length_error("String::insert");
	size_type pos = size_-1;
	size_ = size_ + count;
	if (size_ > capacity_)
		reallocate(size_);
	
	for (size_type i = size_ - 1; pos >= index;)
		data_[i--] = data_[pos--];
	for (size_type i = 0; i < count; ++i)
		data_[index++] = ch;
	return *this;
}

String& String::append(size_type count, char ch)
{
	if (size_ + count > maxsize_)
		throw std::length_error("String::append");
	size_type pos = size_;
	size_ += count;
	if (size_ > capacity_)
		reallocate(size_);
	while (count--) {
		data_[pos++] = ch;
	}
	return *this;
}

String& String::append(const String& str)
{
	return this->append(str, 0, str.size_);
}

String& String::append(const String& str, size_type pos, size_type count)
{
	if (pos > str.size())
		throw std::out_of_range("String::append");
	if (size_ + count > maxsize_)
		throw std::length_error("String::append");
	size_type sz = size_;
	count = (pos + count > str.size_ ? (str.size_ - pos) : count);
	size_ += count;
	if (size_ > capacity_)
		reallocate(size_);
	for (int i = 0; i < count; ++i)
		data_[sz++] = str.data_[pos++];
	return *this;
}

String& String::append(const char* s, size_type count)
{
	if (size_ + count > maxsize_)
		throw std::length_error("String::append");
	size_type sz = size_;
	size_ += count;
	if (size_ > capacity_)
		reallocate(size_);
	memcpy(data_+sz, s, count);
	return *this;
}

String& String::append(const char* s)
{
	return this->append(s, strlen(s));
}

String& String::operator+=(const String& rhs)
{
	return this->append(rhs);
}

String& String::operator+=(char c)
{
	return this->append(1, c);
}

String& String::operator+=(const char* s)
{
	return this->append(s);
}

int String::compare(const String& rhs) const
{
	
}

int String::compare(const char* s) const
{
	
}

void String::resize(size_type count)
{
	if (count > maxsize_)
		throw std::length_error("String::resize(size_type count)");
	resize(count, char());
}

void String::resize(size_type count, char ch)
{
	if (count > maxsize_)
		throw std::length_error("String::resize(size_type count, char ch)");
	if (count == size_) {
		return ;
	} else {
		char* tmp = new char[count];
		if (count < size_) {
			memcpy(tmp, data_, count);
			delete [] data_;
		} else {
			memcpy(tmp, data_, size_);
			delete [] data_;
			for (size_type i = size_; i < count; ++i)
				tmp[i] = ch;
			if (count > capacity_) capacity_ *= 2; // if count > capacity_, capacity_ *= 2.
		}
		size_ = count;
		data_ = tmp;
		tmp = nullptr;
	}
}

void String::swap(String& rhs) noexcept
{
	using std::swap;
	swap(data_, rhs.data_);
	swap(size_, rhs.size_);
	swap(capacity_, rhs.capacity_);
}

// helper: reallocate the memory.
void String::reallocate(size_type size)
{
	if (size * 2 > maxsize_) 
		throw std::length_error("String::expand(size_type size)");
	size_type original_sz = size_;
	size_ = size;
	if (size_ > capacity_ && size_ < 2*capacity_ && capacity_ != 0)
		capacity_ *= 2;
	else
		capacity_ = size;
	char* tmp = new char[capacity_];
	memcpy(tmp, data_, original_sz);
	delete [] data_;
	data_ = tmp;
	tmp = nullptr;
}


// Non-member functions
String operator+(const String& lhs, const String& rhs)
{
	
}

bool operator==(const String& lhs, const String& rhs)
{
	
}

bool operator!=(const String& lhs, const String& rhs)
{
	
}

bool operator<(const String& lhs, const String& rhs)
{
	
}

bool operator>(const String& lhs, const String& rhs)
{
	
}

bool operator<=(const String& lhs, const String& rhs)
{
	
}

bool operator>=(const String& lhs, const String& rhs)
{
	
}

// Input/Output
std::ostream& operator<<(std::ostream& os, const String& rhs)
{
	for (int i = 0; i < rhs.size_; ++i)
		os << rhs.data_[i];
	return os;
}

std::istream& operator>>(std::istream& is, String& rhs)
{
	
}

std::istream& getline(std::istream& is, String& rhs)
{
	
}

#endif
