#include <sstream>
#include "record.h"

Record::Record(ValueType avalue):
    fvalue(avalue)
{
}

ValueType Record::value() const
{
    return fvalue;
}

std::string Record::toString() const
{
    std::ostringstream os;
    os << fvalue;
    return os.str();
}
