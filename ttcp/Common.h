#pragma once

#include <string>

class noncopyable {
public:
    noncopyable() {}
private:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};

struct copyable {

};

class StringArg : copyable {
public:
    StringArg(const char* str_)
        : str(str_)
    {
    }

    StringArg(const std::string& str_)
        : str(str_.c_str())
    {
    }

    const char* c_str() { return str; }
private:
    const char* str;
};

template <typename To, typename From>
inline
To implicit_cast(const From& f)
{
    return f;
}
