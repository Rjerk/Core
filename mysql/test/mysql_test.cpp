#include <string>
#include <iostream>
#include <mysql/mysql.h>
#include <mysql/errmsg.h>

#define SERVER "localhost"
#define USER "sam"
#define PASSWORD "0355"
#define DATABASE "market"

int main()
{
    MYSQL* connection = mysql_init(NULL);
    if (!connection) {
        std::cout << "MySQL initialization failed.\n";
        return -1;
    }
    connection = mysql_real_connect(connection, SERVER, USER,
                                       PASSWORD, DATABASE, 0, NULL, 0);
    if (connection) {
        std::cout << "connection suceessed.\n";
    } else {
        std::cout << "connection failed.\n";
    }

    MYSQL_RES* res_set;
    MYSQL_ROW row;

    int ret;
    if ((ret = mysql_query(connection, "select * from apple"))) {
        if (ret == CR_COMMANDS_OUT_OF_SYNC) {
            std::cerr << "commands were executed in an improper order\n";
        } else if (ret == CR_SERVER_GONE_ERROR) {
            std::cerr << "mysql server has gone away.";
        } else if (ret == CR_SERVER_LOST) {
            std::cerr << "the connection to the server was lost during the query.\n";
        } else {
            std::cerr << "an unknown error occurred.\n";
        }
        return -1;
    }

    res_set = mysql_store_result(connection);
    for (unsigned i = 0; i < mysql_field_count(connection); ++i) {
        row = mysql_fetch_row(res_set);
        if (row == nullptr) {
            break;
        }
        for (unsigned j = 0; j < mysql_num_fields(res_set); ++j) {
            std::cout << row[j] << " ";
        }
        std::cout << std::endl;
    }


    mysql_close(connection);
    return 0;
}
