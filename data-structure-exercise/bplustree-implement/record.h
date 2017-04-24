#ifndef RECORD_H
#define RECORD_H

#include <string>
#include "common.h"

class Record {
public:
    explicit Record(ValueType avalue);
    ValueType value() const;
    std::string toString() const;
private:
    Record(): fValue(0) {}
    ValueType fvalue;
};

#endif
