#ifndef ICMPD_H
#define ICMPD_H

#include "unpicmpd.h"

struct client {
    int connfd; // UNIX domain stream socket to client.
    int family; // AF_INET or AF_INET6.
    int lport; // local port bound to client's UDP socket.
} client[FD_SETSIZE];

int fd4, fd6, listenfd, maxi, maxfd, nready;

fd_set rset, allset;

struct sockaddr_un clntaddr;

int readable_conn(int);
int readable_listen(void);
int readable_v4(void);
int readable_v6(void);

#endif
