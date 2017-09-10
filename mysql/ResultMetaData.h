#ifndef RESULT_META_DATA_H
#define RESULT_META_DATA_H

#include <mysql/mysql.h>
#include <memory>
#include <unordered_map>

namespace rmysql {

class ResultMetaData {
public:
    explicit ResultMetaData(MYSQL_STMT* stmt);

    ~ResultMetaData();

    MYSQL_BIND* data() const { return data_.get(); }

    int columnsReturned() const { return columns_num_; }

    int getInt(int column_index);
    int getInt(const std::string& column_name);
    long long getLong(int column_index);
    long long getLong(const std::string& column_name);
    std::string getString(int column_index);
    std::string getString(const std::string& column_name);
    float getFloat(int column_index);
    float getFloat(const std::string& column_name);

private:
    int getFieldIndex(const std::string& name) const;
    void setFieldName(int i, const std::string& name);
    void makeInt(int);
    void makeFloat(int);
    void makeString(int, size_t);
    void makeLong(int);

private:
    std::unique_ptr<MYSQL_BIND[]> data_;
    int columns_num_;

    union ValType {
        int ival;
        float fval;
        char* sval;
        long long lval;
    };

    std::unique_ptr<ValType[]> vals_;
    std::unique_ptr<unsigned long[]> length_;
    std::unique_ptr<my_bool[]> is_null_;

    std::unordered_map<std::string, int> field_map_;
};


}

#endif
