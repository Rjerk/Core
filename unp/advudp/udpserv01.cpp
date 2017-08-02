#include "unpifi.h"

#undef  MAXLINE
#define MAXLINE 20 // to see datagram truncation.

void dg_echo(int sockfd, SA* pclntaddr, socklen_t clnt_len)
{
    const int on = 1; (void) on;
#ifdef IP_RECVDSTADDR
    if (setsockopt(sockfd, IPPROTO_IP, IP_RECVDSTADDR, &on, sizeof(on)) < 0) {
        err_ret("setsockopt of IP_RECVDSTADDR");
    }
#endif

#ifdef IP_RECVIF
    if (setsockopt(sockfd, IPPROTO_IP, IP_RECVIF, &on, sizeof(on)) < 0) {
        err_ret("setsockopt of IP_RECVIF");
    }
#endif

    struct in_addr in_zero;
    bzero(&in_zero, sizeof(struct in_addr));

    char msg[MAXLINE], str[INET6_ADDRSTRLEN], ifname[IFNAMSIZ];
    ssize_t n;
    struct unp_in_pktinfo pktinfo;
    socklen_t len;
    int flags;
    for ( ; ; ) {
        len = clnt_len;
        flags = 0;
        n = Recvfrom_flags(sockfd, (void *) msg, MAXLINE, &flags, pclntaddr, &len, &pktinfo);
        printf("%ld-byte datagram from %s", n, Sock_ntop(pclntaddr, len));
        if (memcmp(&pktinfo.ipi_addr, &in_zero, sizeof(in_zero)) < 0) {
            printf(", to %s", Inet_ntop(AF_INET, &pktinfo.ipi_addr, str, sizeof(str)));
        }

        if (pktinfo.ipi_ifindex > 0) {
            printf(", recv i/f = %s", If_indextoname(pktinfo.ipi_ifindex, ifname));
        }

#ifdef MSG_TRUNC
    if (flags & MSG_TRUNC) {
        printf(" (datagram truncated)");
    }
#endif

#ifdef MSG_CTRUNC
    if (flags & MSG_CTRUNC) {
        printf(" (control info truncated)");
    }
#endif

#ifdef MSG_BCAST
    if (flags & MSG_BCAST) {
        printf(" (broadcast)");
    }
#endif

#ifdef MSG_MCAST
    if (flags & MSG_MCAST) {
        printf (" (multicast)");
    }
#endif

    Sendto(sockfd, msg, n, 0, pclntaddr, len);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage: ./udpserv01 <port>");
    }
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr, clntaddr;
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SA *) &clntaddr, sizeof(clntaddr));
}
