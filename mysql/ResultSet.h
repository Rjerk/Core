#ifndef RESULT_SET
#define RESULT_SET

#include <boost/noncopyable.hpp>
#include <mysql/mysql.h>
#include <memory>
#include <string>

namespace rmysql {

class ResultMetaData;

class ResultSet : boost::noncopyable {
public:
    explicit ResultSet(MYSQL_STMT* stmt);

    ~ResultSet();

    bool next();

    int getInt(int column_index);
    int getInt(const std::string& column_name);
    long long getLong(int column_index);
    long long getLong(const std::string& column_name);
    std::string getString(int column_index);
    std::string getString(const std::string& column_name);
    float getFloat(int column_index);
    float getFloat(const std::string& column_name);

private:
    MYSQL_STMT* stmt_;
    std::unique_ptr<ResultMetaData> meta_data_; // owner.
    int rows_;
};

}


#endif
