/**********************************
 * FILE NAME: Log.h
 *
 * DESCRIPTION: Header file of Log class
 **********************************/

#ifndef _LOG_H_
#define _LOG_H_

#include "stdincludes.h"
#include "Params.h"
#include "Member.h"

/*
 * Macros
 */
// number of writes after which to flush file
namespace {
    const int MAXWRITES {1};
    const std::string MAGIC_NUMBER {"CS425"};
    const std::string DBG_LOG {"dbg.log"};
    const std::string STATS_LOG {"stats.log"};
}
/**
 * CLASS NAME: Log
 *
 * DESCRIPTION: Functions to log messages in a debug log
 */
class Log {
private:
	Params *par_;
	bool first_time_{false};
public:
	explicit Log(Params *p);
	explicit Log(const Log &anotherLog);
	Log& operator=(const Log &anotherLog);

	virtual ~Log();

	void LOG(Address *, const std::string& str, ...);
	void logNodeAdd(Address *, Address *);
	void logNodeRemove(Address *, Address *);
};

#endif /* _LOG_H_ */
