#include "Statement.h"
#include "Binder.h"
#include "ResultSet.h"

#include <cassert>
#include <iostream>

namespace rmysql {

using std::string;

Statement::Statement(MYSQL* conn, const string& sql)
    : conn_(conn)
{
    auto ret = ::mysql_stmt_init(conn_);
    assert(ret);
    stmt_.reset(ret);
    state_ = STMT_STATE::INITED;

    int status_value = ::mysql_stmt_prepare(stmt_.get(), sql.c_str(), sql.size()); (void) status_value;
    assert(status_value == 0);

    int param_num = 0;
    if ((param_num = ::mysql_stmt_param_count(stmt_.get())) > 0) {
        binder_.reset(new Binder(param_num));
    }
    state_ = STMT_STATE::COMPILED;

    std::cout << "Statement ctor\n";
}

Statement::~Statement()
{
    ::mysql_stmt_close(stmt_.get());
    std::cout << "Statement dtor..\n";
}

void Statement::execute()
{
    if (stmt_) {
        auto ret = ::mysql_stmt_bind_param(stmt_.get(), binder_.get()->data()); (void) ret;
        assert(ret == 0);
    }

    auto ret = ::mysql_stmt_execute(stmt_.get()); (void) ret;
    assert(ret == 0);

    state_ = STMT_STATE::EXECUTED;
}

int Statement::affectedRows()
{
    return ::mysql_stmt_affected_rows(stmt_.get());
}

ResultSet* Statement::getResultSet()
{
    assert(state_ == STMT_STATE::EXECUTED);
    return new ResultSet(stmt_.get());
}

void Statement::bindIntParam(int i, int val)
{
    assert(i >= 0 && binder_);
    binder_.get()->bind(i, val);
}

void Statement::bindFloatParam(int i, float val)
{
    assert(i >= 0 && binder_);
    binder_.get()->bind(i, val);
}

void Statement::bindLongParam(int i, long long val)
{
    assert(i >= 0 && binder_);
    binder_.get()->bind(i, val);
}

void Statement::bindStrParam(int i, const std::string val)
{
    assert(i >= 0 && binder_);
    binder_.get()->bind(i, val);
}

}
