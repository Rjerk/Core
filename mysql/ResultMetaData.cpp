#include "ResultMetaData.h"
#include <algorithm>
#include <cassert>
#include <iostream>


namespace rmysql {

namespace {

class ResultMetaDataHander {
public:
    explicit ResultMetaDataHander(MYSQL_STMT* stmt)
    {
        meta_ = ::mysql_stmt_result_metadata(stmt);
    }

    ~ResultMetaDataHander()
    {
        ::mysql_free_result(meta_);
    }

    operator MYSQL_RES*()
    {
        return meta_;
    }

private:
    MYSQL_RES* meta_;
};

#define freeIfString(i) \
{ if (data_[i].buffer_type == MYSQL_TYPE_STRING) delete [] vals_[i].sval; }

}

ResultMetaData::ResultMetaData(MYSQL_STMT* stmt)
{
    ResultMetaDataHander handler(stmt);
    if (!handler) {
        return ;
    }

    columns_num_ = ::mysql_num_fields(handler);
    auto fields = ::mysql_fetch_fields(handler);

    data_.reset(new MYSQL_BIND[columns_num_]);
    length_.reset(new unsigned long[columns_num_]);
    vals_.reset(new ValType[columns_num_]);
    is_null_.reset(new my_bool[columns_num_]);

    std::fill(length_.get(), length_.get() + columns_num_, 0);
    std::fill(is_null_.get(), is_null_.get() + columns_num_, 0);

    for (int i = 0; i < columns_num_; ++i ) {
        data_[i].buffer_type = MYSQL_TYPE_NULL;
        data_[i].buffer_length = 0;
        data_[i].buffer = nullptr;
        data_[i].length = &length_[i];
        data_[i].is_null = &is_null_[i];
        data_[i].is_unsigned = 0;
        data_[i].error = nullptr;
    }

    for (int i = 0; i < columns_num_; ++i) {
        switch (fields[i].type) {
            case MYSQL_TYPE_LONG:
                makeInt(i);
                break;
            case MYSQL_TYPE_LONGLONG:
                makeLong(i);
                break;
            case MYSQL_TYPE_STRING:
                makeString(i, fields[i].length);
                break;
            case MYSQL_TYPE_FLOAT:
                makeFloat(i);
                break;
            default:
                break;
        }
        setFieldName(i, fields[i].name);
    }

    std::cout << "ResultMetaData ctor\n";
}

ResultMetaData::~ResultMetaData()
{
    for (auto i = 0; i < columns_num_; ++i) {
        freeIfString(i);
    }
    std::cout << "ResultMetaData dtor\n";
}

int ResultMetaData::getInt(int i)
{
    return is_null_[i] ? 0 : vals_[i].ival;
}

int ResultMetaData::getInt(const std::string& column_name)
{
    return getInt(getFieldIndex(column_name));
}

long long ResultMetaData::getLong(int i)
{
    return is_null_[i] ? 0 : vals_[i].ival;
}

long long ResultMetaData::getLong(const std::string& column_name)
{
    return getLong(getFieldIndex(column_name));
}

std::string ResultMetaData::getString(int i)
{
    if (data_[i].buffer_type == MYSQL_TYPE_STRING) {
        return std::string(vals_[i].sval, length_[i]);
    } else if (data_[i].buffer_type == MYSQL_TYPE_LONG) {
        return std::to_string(getInt(i));
    } else if (data_[i].buffer_type == MYSQL_TYPE_LONGLONG) {
        return std::to_string(getLong(i));
    } else if (data_[i].buffer_type == MYSQL_TYPE_FLOAT) {
        return std::to_string(getFloat(i));
    } else {
        return "";
    }
}

std::string ResultMetaData::getString(const std::string& column_name)
{
    return getString(getFieldIndex(column_name));
}

float ResultMetaData::getFloat(int i)
{
    return is_null_[i] ? 0 : vals_[i].fval;
}

float ResultMetaData::getFloat(const std::string& column_name)
{
    return getFloat(getFieldIndex(column_name));
}

int ResultMetaData::getFieldIndex(const std::string& name) const
{
    auto iter = field_map_.find(name); (void) iter;
    assert(iter != field_map_.end());
    return iter->second;
}

void ResultMetaData::setFieldName(int i, const std::string& name)
{
    field_map_.insert(std::pair<std::string, int>(name, i));
}

void ResultMetaData::makeInt(int i)
{
    freeIfString(i);
    data_[i].buffer_type = MYSQL_TYPE_LONG;
    data_[i].buffer = &vals_[i].ival;
    data_[i].buffer_length = length_[i] = sizeof(int);
}

void ResultMetaData::makeFloat(int i)
{
    freeIfString(i);
    data_[i].buffer_type = MYSQL_TYPE_FLOAT;
    data_[i].buffer = &vals_[i].fval;
    data_[i].buffer_length = length_[i] = sizeof(float);
}

void ResultMetaData::makeString(int i, size_t size)
{
    freeIfString(i);
    data_[i].buffer_type = MYSQL_TYPE_STRING;
    data_[i].buffer = vals_[i].sval = new char[size];
    data_[i].buffer_length = length_[i] = size;
}

void ResultMetaData::makeLong(int i)
{
    freeIfString(i);
    data_[i].buffer_type = MYSQL_TYPE_LONGLONG;
    data_[i].buffer = &vals_[i].lval;
    data_[i].buffer_length = length_[i] = sizeof(long long);

}

}
