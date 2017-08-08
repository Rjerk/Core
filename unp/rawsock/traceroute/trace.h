#ifndef TRACE_H
#define TRACE_H

#include "../../unp.h"

#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>

#include <netinet/ip6.h>
#include <netinet/icmp6.h>

#define IPV6

#define BUFSIZE 1500

char recvbuf[BUFSIZE];
char sendbuf[BUFSIZE];

struct rec { // format of outgoing UDP data.
    u_short rec_seq; // sequence number.
    u_short rec_ttl; // TTL packet left with.
    struct timeval rec_tv; // time packet left.
};

int datalen = sizeof(struct rec); // # bytes of data following ICMP hearder.
char* host = NULL;
u_short sport, dport = 32768 + 666;
int nsent;
pid_t pid;
int probe, nprobes = 3;
int sendfd, recvfd; // send on UDP sock, read on raw ICMP sock.
int ttl, max_ttl = 30;
int verbose = 0;

const char* icmpcode_v4(int);
const char* icmpcode_v6(int);
int recv_v4(int, struct timeval *);
int recv_v6(int, struct timeval *);
void sig_alrm(int);
void traceloop(void);
void tv_sub(struct timeval *, struct timeval *);

struct proto {
    const char* (*icmpcode)(int);
    int (*recv)(int, struct timeval *);
    struct sockaddr* sasend;
    struct sockaddr* sarecv;
    struct sockaddr* salast;
    struct sockaddr* sabind;
    socklen_t salen;
    int icmpproto;
    int ttllevel;
    int ttloptname;
} *pr;

#endif
