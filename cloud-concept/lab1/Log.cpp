/**********************************
 * FILE NAME: Log.h
 *
 * DESCRIPTION: Log class definition
 **********************************/

#include "Log.h"

Log::Log(Params *p):
  par_{p}
{
}

Log::Log(const Log &another_log) {
	this->par_ = another_log.par_;
	this->first_time_ = another_log.first_time_;
}

Log& Log::operator=(const Log& another_log) {
	this->par_ = another_log.par_;
	this->first_time_ = another_log.first_time_;
	return *this;
}

Log::~Log() {}

// DESCRIPTION: Print out to file dbg.log, along with Address of node.
void Log::LOG(Address *addr, const std::string& str, ...)
{
	static FILE *fp;
	static FILE *fp2;
	static int numwrites;
	static char stdstring[30];
	static char stdstring2[40];
	static char stdstring3[40]; 
	static int dbg_opened=0;

	if (dbg_opened != 639){
		numwrites=0;

		stdstring2[0]=0;

		strcpy(stdstring3, stdstring2);

		strcat(stdstring2, DBG_LOG.data());
		strcat(stdstring3, STATS_LOG.data());

		fp = fopen(stdstring2, "w");
		fp2 = fopen(stdstring3, "w");

		dbg_opened=639;
	} else  {
	  sprintf(stdstring, "%d.%d.%d.%d:%d ", addr->addr[0], addr->addr[1], addr->addr[2], addr->addr[3], *(short *)&addr->addr[4]);
  }

	va_list vararglist;
	static char buffer[30000];
	va_start(vararglist, str.data());
	vsprintf(buffer, str.data(), vararglist);
	va_end(vararglist);

	if (!first_time_) {
		int magicNumber = 0;
    std::string magic = MAGIC_NUMBER;
		int len = magic.length();
		for ( int i = 0; i < len; i++ ) {
			magicNumber += (int)magic.at(i);
		}
		fprintf(fp, "%x\n", magicNumber);
		first_time_ = true;
	}

	if (memcmp(buffer, "#STATSLOG#", 10) == 0) {
		fprintf(fp2, "\n %s", stdstring);
		fprintf(fp2, "[%d] ", par_->getcurrtime());

		fprintf(fp2, buffer);
	}
	else{
		fprintf(fp, "\n %s", stdstring);
		fprintf(fp, "[%d] ", par_->getcurrtime());
		fprintf(fp, buffer);

	}

	if (++numwrites >= MAXWRITES) {
		fflush(fp);
		fflush(fp2);
		numwrites = 0;
	}

}

/**
 * FUNCTION NAME: logNodeAdd
 *
 * DESCRIPTION: To Log a node add
 */
void Log::logNodeAdd(Address *this_node, Address *added_addr) {
	static char stdstring[100];
	sprintf(stdstring, "Node %d.%d.%d.%d:%d joined at time %d", added_addr->addr[0], added_addr->addr[1], added_addr->addr[2], added_addr->addr[3], *(short *)&added_addr->addr[4], par_->getcurrtime());
  LOG(this_node, stdstring);
}

/**
 * FUNCTION NAME: logNodeRemove
 *
 * DESCRIPTION: To log a node remove
 */
void Log::logNodeRemove(Address *this_node, Address *removed_addr) {
	static char stdstring[30];
	sprintf(stdstring, "Node %d.%d.%d.%d:%d removed at time %d", removed_addr->addr[0], removed_addr->addr[1], removed_addr->addr[2], removed_addr->addr[3], *(short *)&removed_addr->addr[4], par_->getcurrtime());
  LOG(this_node, stdstring);
}
