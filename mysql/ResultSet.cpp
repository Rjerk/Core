#include "ResultSet.h"
#include "ResultMetaData.h"
#include <cassert>
#include <iostream>

namespace rmysql {

ResultSet::ResultSet(MYSQL_STMT* stmt)
    : meta_data_(new ResultMetaData(stmt))
{
    stmt_ = stmt;
    auto ret = ::mysql_stmt_bind_result(stmt_, meta_data_.get()->data());
    assert(ret == 0);

    ret = ::mysql_stmt_store_result(stmt_);
    assert(ret == 0);

    rows_ = ::mysql_stmt_affected_rows(stmt_);

    std::cout << "ResultSet ctor\n";
}

ResultSet::~ResultSet()
{
    std::cout << "ResultSet dtor\n";
}

bool ResultSet::next()
{
    if (rows_ == 0) {
        return false;
    }

    switch (::mysql_stmt_fetch(stmt_)) {
        case 0:
            return true;
        case MYSQL_NO_DATA:
            return false;
        default:
            std::cerr << "An error occurred: " << ::mysql_stmt_error(stmt_);
            break;
    }
    return false;
}


int ResultSet::getInt(int column_index)
{
    return meta_data_.get()->getInt(column_index);
}

int ResultSet::getInt(const std::string& column_name)
{
    return meta_data_.get()->getInt(column_name);
}

long long ResultSet::getLong(int column_index)
{
    return meta_data_.get()->getLong(column_index);
}

long long ResultSet::getLong(const std::string& column_name)
{
    return meta_data_.get()->getLong(column_name);
}

std::string ResultSet::getString(int column_index)
{
    return meta_data_.get()->getString(column_index);
}

std::string ResultSet::getString(const std::string& column_name)
{
    return meta_data_.get()->getString(column_name);
}

float ResultSet::getFloat(int column_index)
{
    return meta_data_.get()->getFloat(column_index);
}

float ResultSet::getFloat(const std::string& column_name)
{
    return meta_data_.get()->getFloat(column_name);
}

}
