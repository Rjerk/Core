#ifndef RECORD_H
#define RECORD_H

#include "common.h"

class Record {
public:
	Record(ValueType value_):
		value(value_)
	{
	}
	
	ValueType getValue() const
	{
		return value;
	}
private:
	ValueType value;
};


#endif
