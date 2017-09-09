#ifndef BINDER_H
#define BINDER_H

#include <mysql/mysql.h>

namespace rmysql {

class Binder {
public:
    MYSQL_BIND* data();

};

}


#endif
