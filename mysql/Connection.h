#ifndef CONNECTION_H
#define CONNECTION_H

#include <mysql/mysql.h>
#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

namespace rmysql {

class Statement;

using std::string;

class Connection : boost::noncopyable {
public:
    explicit Connection(const string& host, unsigned int port,
                        const string& user, const string& passwd, const string& db);
    explicit Connection(const string& sock,
                        const string& user, const string& passwd, const string& db);

    ~Connection();

    operator bool ();

    Statement* prepare(const string& sql);

    void charset(const std::string& cs);

private:
    MYSQL* conn_; // owner.
};


}


#endif
