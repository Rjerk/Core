#include "ping.h"

struct proto proto_v4 = { proc_v4, send_v4, NULL, NULL, NULL, 0, IPPROTO_ICMP };

#ifdef IPV6
struct proto proto_v6 = { proc_v6, send_v6, init_v6, NULL, NULL, 0, IPPROTO_ICMPV6 };
#endif

void init_v6()
{
#ifdef IPV6
    int on = 1;
    if (verbose == 0) {
        struct icmp6_filter myfilt;
        ICMP6_FILTER_SETBLOCKALL(&myfilt);
        ICMP6_FILTER_SETPASS(ICMP6_ECHO_REPLY, &myfilt);
        setsockopt(sockfd, IPPROTO_IPV6, ICMP6_FILTER, &myfilt, sizeof(myfilt));
    }
    setsockopt(sockfd, IPPROTO_IPV6, IPV6_RECVHOPLIMIT, &on, sizeof(on));

#endif
}

void proc_v4(char* ptr, ssize_t len, struct msghdr*, struct timeval* tvrecv)
{
    struct ip* ip = (struct ip *) ptr; // start of IP header.
    int hlen1 = ip->ip_hl << 2; // length of IP header.
    if (ip->ip_p != IPPROTO_ICMP) {
        return ; // not ICMP.
    }

    struct icmp* icmp = (struct icmp *) (ptr + hlen1); // start of ICMP header.
    int icmplen;
    if ((icmplen = len - hlen1) < 8) {
        return ; // malformed packet.
    }

    if (icmp->icmp_type == ICMP_ECHOREPLY) {
        if (icmp->icmp_id != pid) {
            return ; // not a respond to our ECHO_REQUEST.
        }
        if (icmplen < 16) {
            return ; // not enough data to use.
        }

        struct timeval* tvsend = (struct timeval *) icmp->icmp_data;
        tv_sub(tvrecv, tvsend);
        double rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

        printf("%d bytes from %s: seq = %u ttl = %d rtt = %.3f ms\n",
                icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
                icmp->icmp_seq, ip->ip_ttl, rtt);

    } else if (verbose) {
        printf(" %d bytes from %s: type = %d code = %d\n",
                icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
                icmp->icmp_type, icmp->icmp_code);
    }
}

void proc_v6(char* ptr, ssize_t len, struct msghdr* msg, struct timeval* tvrecv)
{
#ifdef IPV6
    if (len < 8) {
        return ; // malformed packet.
    }

    struct icmp6_hdr* icmp6 = (struct icmp6_hdr *) ptr;
    if (icmp6->icmp6_type == ICMP6_ECHO_REPLY) {
        if (icmp6->icmp6_id != pid) {
            return ; // not a respond to out ECHO_REQUEST.
        }

        if (len < 16) {
            return ; // not enough data to use.
        }

        struct timeval* tvsend = (struct timeval *) (icmp6 + 1);
        tv_sub(tvsend, tvrecv);
        double rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

        int hlim = -1;
        struct cmsghdr* cmsg = NULL;
        for (cmsg = CMSG_FIRSTHDR(msg); cmsg != NULL; cmsg = CMSG_NXTHDR(msg, cmsg)) {
            if (cmsg->cmsg_level == IPPROTO_IPV6 && cmsg->cmsg_type == IPV6_HOPLIMIT) {
                hlim = *(uint32_t *) CMSG_DATA(cmsg);
                break;
            }
        }
        printf("%ld bytes from %s: seq = %u hlim = ",
                len, Sock_ntop_host(pr->sarecv, pr->salen),
                icmp6->icmp6_seq);
        if (hlim == -1) {
            printf("???");
        } else {
            printf("%d", hlim);
        }

        printf(", rtt = %.3f ms\n", rtt);
    } else if (verbose) {
        printf(" %ld bytes from %s: type = %d code = %d\n",
                len, Sock_ntop_host(pr->sarecv, pr->salen),
                icmp6->icmp6_type, icmp6->icmp6_code);
    }
#endif
}

void readloop(void)
{
    sockfd = Socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto);
    setuid(getuid());
    if (pr->finit) {
        (*pr->finit)();
    }

    int size = 64 * 1024;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

    sig_alrm(SIGALRM); // send first packet.

    char recvbuf[MAXLINE];
    struct iovec iov;
    iov.iov_base = recvbuf;
    iov.iov_len = sizeof(recvbuf);

    char controlbuf[MAXLINE];
    struct msghdr msg;
    msg.msg_name = pr->sarecv;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = controlbuf;

    struct timeval tval;
    for ( ; ; ) {
        msg.msg_namelen = pr->salen;
        msg.msg_controllen = sizeof(controlbuf);
        ssize_t n = recvmsg(sockfd, &msg, 0);
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                err_sys("recvmsg error");
            }
        }
        Gettimeofday(&tval, NULL);
        (*pr->fproc)(recvbuf, n, &msg, &tval);
    }
}

void send_v4(void)
{
    struct icmp* icmp = (struct icmp *) sendbuf;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_id = pid;
    icmp->icmp_seq = nsent++;
    memset(icmp->icmp_data, 0xa5, datalen); // fill with pattern;
    Gettimeofday((struct timeval *) icmp->icmp_data, NULL);

    int len = 8 + datalen; // checksum ICMP header and data.
    icmp->icmp_cksum = 0;
    icmp->icmp_cksum = in_cksum((u_short *) icmp, len);

    Sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen);
}

void send_v6()
{
#ifdef IPV6
    int len;
    struct icmp6_hdr* icmp6 = (struct icmp6_hdr *) sendbuf;
    icmp6->icmp6_type = ICMP6_ECHO_REQUEST;
    icmp6->icmp6_code = 0;
    icmp6->icmp6_id = pid;
    icmp6->icmp6_seq = nsent++;
    memset((icmp6 + 1), 0xa5, datalen); // fill with pattern.
    Gettimeofday((struct timeval *)(icmp6 + 1), NULL);

    len = 8 + datalen; // 8-byte ICMPv6 header.
    Sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen);
#endif
}

void sig_alrm(int)
{
    (*pr->fsend)();

    alarm(1);
    return ;
}

void tv_sub(struct timeval* out, struct timeval* in)
{
    if ((out->tv_usec -= in->tv_usec) < 0) {
        --out->tv_sec;
        out->tv_usec += 1000000;
    }
    out->tv_sec -= in->tv_sec;
}

uint16_t in_cksum(uint16_t* addr, int len)
{
    int nleft = len;
    uint32_t sum = 0;
    uint16_t* w = addr;
    uint16_t answer = 0;

    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    if (nleft == 1) {
        *(unsigned char *)(&answer) = *(unsigned char *) w;
        sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xffff); // add hi 16 to low 16.
    sum += (sum >> 16); // add carry;
    answer = ~sum; // truncate to 16 bits.
    return answer;
}

int main(int argc, char** argv)
{
    int c;
    opterr = 0; // don't want getopt() writing to stderr.
    while ((c = getopt(argc, argv, "v")) != -1) {
        switch (c) {
            case 'v':
                ++verbose;
                break;
            case '?':
                err_quit("unrecognized option: %c", c);
        }
    }

    if (optind != argc - 1) {
        err_quit("usage: ./ping [ -v ] <hostname>");
    }

    host = argv[optind];

    pid = getpid() & 0xffff; // ICMP ID field is 16 bits.

    Signal(SIGALRM, sig_alrm);

    struct addrinfo* ai = Host_serv(host, NULL, 0, 0);

    char* h = Sock_ntop_host(ai->ai_addr, ai->ai_addrlen);

    printf("PING %s (%s): %d data bytes\n",
            ai->ai_canonname ? ai->ai_canonname : h,
            h,
            datalen);

    if (ai->ai_family == AF_INET) {
        pr = &proto_v4;
    }
#ifdef IPV6
    else if (ai->ai_family == AF_INET6) {
        pr = &proto_v6;
        if (IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *) ai->ai_addr)->sin6_addr)) {
            err_quit("connot ping IPv4-mapped IPv6 address");
        }
    }
#endif
    else {
        err_quit("unknown address family %d", ai->ai_family);
    }

    pr->sasend = ai->ai_addr;
    pr->sarecv = (struct sockaddr *) Calloc (1, ai->ai_addrlen);
    pr->salen = ai->ai_addrlen;

    readloop();

    exit(0);

}
