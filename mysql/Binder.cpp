#include "Binder.h"
#include <cstring>
#include <cassert>
#include <iostream>

namespace rmysql {

Binder::Binder(size_t count)
    : data_(new MYSQL_BIND[count]), count_(count), val_(new ValueType[count_])
{
    for (size_t i = 0; i < count_; ++i) {
        ::bzero(&data_[i], sizeof(data_[i]));
        data_[i].buffer_type = MYSQL_TYPE_NULL;
        data_[i].buffer_length = 0;
        data_[i].buffer = nullptr;
    }

    std::cout << "Binder ctor\n";
}

Binder::~Binder()
{
    if (val_) {
        for (size_t i = 0; i < count_; ++i) {
            if (data_[i].buffer_type == MYSQL_TYPE_STRING) {
                delete [] (char*) data_[i].buffer;
            }
        }
    }
    std::cout << "Binder dtor\n";
}

void Binder::bind(int i, int val)
{
    assert(i < count_);

    data_[i].buffer_type = MYSQL_TYPE_LONG;
    val_[i].ival = val;
    data_[i].buffer = &val_[i].ival;
}

void Binder::bind(int i, long long val)
{
    assert(i < count_);

    data_[i].buffer_type = MYSQL_TYPE_LONGLONG;
    val_[i].lval = val;
    data_[i].buffer = &val_[i].lval;
}

void Binder::bind(int i, float val)
{
    assert(i < count_);

    data_[i].buffer_type = MYSQL_TYPE_FLOAT;
    val_[i].fval = val;
    data_[i].buffer = &val_[i].fval;
}

void Binder::bind(int i, const std::string& val)
{
    assert(i < count_);

    data_[i].buffer_type = MYSQL_TYPE_STRING;
    data_[i].buffer_length = val.size();
    data_[i].buffer = val_[i].sval = new char[val.size()];
    ::memcpy(data_[i].buffer, val.c_str(), val.size());
}

}
