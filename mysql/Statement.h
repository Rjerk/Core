#ifndef STATEMENT_H
#define STATEMENT_H

#include <mysql/mysql.h>
#include <boost/noncopyable.hpp>

#include <memory>
#include <string>

namespace rmysql {

class Binder;
class ResultSet;

class Statement : boost::noncopyable {
public:
    enum class STMT_STATE {
        INITED,
        COMPILED,
        EXECUTED
    };

    explicit Statement(MYSQL* conn, const std::string& sql);

    ~Statement();

    void execute();

    int affectedRows();

    ResultSet* getResultSet();

    void bindIntParam(int i, int val);
    void bindFloatParam(int i, float val);
    void bindLongParam(int i, long long val);
    void bindStrParam(int i, const std::string val);
private:
    MYSQL* conn_; // not owner.
    std::unique_ptr<MYSQL_STMT> stmt_; // owner.
    std::unique_ptr<Binder> binder_; // owner.
    STMT_STATE state_;
};

}

#endif
