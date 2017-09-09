#ifndef RESULT_SET
#define RESULT_SET

#include <boost/noncopyable.hpp>
#include <mysql/mysql.h>
#include <memory>

namespace rmysql {

class ResultSet : boost::noncopyable {
public:
    explicit ResultSet(MYSQL_STMT* stmt);

    ~ResultSet();

private:
    std::unique_ptr<MYSQL_STMT> stmt_;
    int rows_;
};

}


#endif
