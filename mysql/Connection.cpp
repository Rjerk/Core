#include "Connection.h"
#include "Statement.h"

#include <iostream>
#include <cassert>

namespace rmysql {

using std::cerr;

Connection::Connection(const string& host, unsigned int port,
                       const string& user, const string& passwd, const string& db)
    : conn_(::mysql_init(NULL))
{
    auto ret = ::mysql_real_connect(conn_, host.c_str(), user.c_str(), passwd.c_str(),
                             db.c_str(), port, nullptr, 0); (void) ret;
    assert(ret);
    // use SET NAMES 'utf8' before query.
    charset("utf8");

    std::cout << "Connection ctor\n";
}

Connection::Connection(const string& sock,
                       const string& user, const string& passwd, const string& db)
    : conn_(::mysql_init(NULL))
{
    auto ret = ::mysql_real_connect(conn_, nullptr, user.c_str(), passwd.c_str(),
                               db.c_str(), 0, sock.c_str(), 0); (void) ret;
    assert(ret);
    charset("utf8");
    std::cout << "Connection ctor\n";
}

Connection::~Connection()
{
    std::cout << "Connection dtor\n";
    ::mysql_close(conn_);
}

Connection::operator bool()
{
    // check whether the connection to server is working.
    return ::mysql_ping(conn_) == 0;
}

Statement* Connection::prepare(const string& sql)
{
    return new Statement(conn_, sql);
}

void Connection::charset(const string& cs)
{
    string sql;
    sql.assign("set NAMES '").append(cs).append("'");
    assert(::mysql_real_query(conn_, sql.c_str(), sql.size()) == 0);
}

}
