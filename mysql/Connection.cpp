#include "Connection.h"
#include "Statement.h"

#include <iostream>
#include <cassert>

namespace rmysql {

using std::cerr;

Connection::Connection(const string& host, unsigned int port,
                       const string& user, const string& passwd, const string& db)
    : conn_(new MYSQL)
{
    auto ret = ::mysql_init(conn_.get());
    assert(ret);
    ret = mysql_real_connect(conn_.get(), host.c_str(), user.c_str(), passwd.c_str(),
                             db.c_str(), port, nullptr, 0);
    assert(ret);
    // use SET NAMES 'utf8' before query.
    charset("utf8");
}

Connection::Connection(const string& sock,
                       const string& user, const string& passwd, const string& db)
    : conn_(new MYSQL)
{
    auto ret = ::mysql_init(conn_.get());
    assert(ret);
    ret = ::mysql_real_connect(conn_.get(), nullptr, user.c_str(), passwd.c_str(),
                               db.c_str(), 0, sock.c_str(), 0);
    charset("utf8");
}

Connection::~Connection()
{
    ::mysql_close(conn_.get());
}

Connection::operator bool()
{
    // check whether the connection to server is working.
    return ::mysql_ping(conn_.get()) == 0;
}

Statement* Connection::prepare(const string& sql)
{
    return new Statement(conn_.get(), sql);
}


void Connection::charset(const string& cs)
{
    string sql;
    sql.assign("SET NAMES '").append(cs).append("'");
    assert(::mysql_real_query(conn_.get(), sql.c_str(), sql.size()));
}

}
