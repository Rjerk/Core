//#ifndef WEB_H
//#define WEB_H

#pragma once

#include "../unp.h"

#define MAXFILES 20
#define SERV "80" // port number or service name.

struct file {
    char* f_name;
    char* f_host;
    int   f_fd;
    int   f_flags;
} file[MAXFILES];

#define F_CONNECTING 1 // connect() in progress.
#define F_READING 2 // connect() complete; now reading.
#define F_DONE 4 // all done.

#define GET_CMD "GET %s HTTP/1.0\r\n\r\n"

int nconn, nfiles, nlefttoconn, nlefttoread, maxfd;
fd_set rset, wset;

void home_page(const char*, const char*);
void start_connect(struct file*);
void write_get_cmd(struct file*);

//#endif
