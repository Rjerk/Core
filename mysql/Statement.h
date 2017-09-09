#ifndef STATEMENT_H
#define STATEMENT_H

#include <mysql/mysql.h>
#include <boost/noncopyable.hpp>

#include <memory>
#include <string>

namespace rmysql {

class Binder;

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

private:
    std::unique_ptr<MYSQL> conn_;
    std::unique_ptr<MYSQL_STMT> stmt_;
    std::unique_ptr<Binder> binder_;
    STMT_STATE state_;
};

}

#endif
