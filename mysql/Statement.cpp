#include "Statement.h"
#include "Binder.h"
#include "ResultSet.h"

#include <cassert>

namespace rmysql {

using std::string;

Statement::Statement(MYSQL* conn, const string& sql)
    : conn_(conn)
{
    auto ret = ::mysql_stmt_init(conn_.get());
    assert(ret);
    stmt_.reset(ret);
    state_ = STMT_STATE::INITED;

    int status_value = ::mysql_stmt_prepare(stmt_.get(), sql.c_str(), sql.size()); (void) status_value;
    assert(status_value);

    int param_num = 0;
    if ((param_num = ::mysql_stmt_param_count(stmt_.get())) > 0) {
        binder_.reset(new Binder());
    }
    state_ = STMT_STATE::COMPILED;
}

Statement::~Statement()
{
    ::mysql_stmt_close(stmt_.get());
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
    return new ResultSet(stmt_);
}

}
