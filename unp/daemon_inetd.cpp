#include "unp.h"

extern int daemon_proc;

void daemon_inetd(const char* pname, int facility)
{
    daemon_proc = 1;
    openlog(pname, LOG_PID, facility);
}
