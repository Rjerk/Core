#ifndef BINDER_H
#define BINDER_H

#include <mysql/mysql.h>
#include <string>
#include <memory>

namespace rmysql {

class Binder {
public:
    explicit Binder(size_t size);

    ~Binder();

    MYSQL_BIND* data() const { return data_.get(); }

    size_t count() const { return count_; }

    void bind(int i, int val);
    void bind(int i, long long val);
    void bind(int i, float val);
    void bind(int i, const std::string& val);
private:
    std::unique_ptr<MYSQL_BIND[]> data_;
    size_t count_;

    union ValueType {
        int ival;
        float fval;
        long long lval;
        char* sval;
    };

    std::unique_ptr<ValueType[]> val_;
};

}


#endif
