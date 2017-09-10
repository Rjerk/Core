#include "rmysql.h"
#include "Binder.h"

#include <iostream>
#include <cassert>
#include <memory>

int main()
{
    using namespace rmysql;
    std::unique_ptr<Connection> conn(new Connection{"localhost", 8888, "sam", "0355", "market"});

    std::unique_ptr<Statement> stmt{conn->prepare("select * from apple where number = ?")};
    stmt->bindIntParam(0, 10);
    stmt->execute();

    std::unique_ptr<ResultSet> result_set{stmt->getResultSet()};

    while (result_set->next()) {
        std::cout << "number: " << result_set->getInt("number")
                  << " price: " << result_set->getInt("price") << std::endl;
    }
}
