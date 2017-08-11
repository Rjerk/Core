#include "unpicmpd.h"

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    Sock_bind_wild(sockfd, pservaddr->sa_family);
    int icmpfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

    struct sockaddr_un sun;
    sun.sun_family = AF_LOCAL;
    strncpy(sun.sun_path, ICMPD_PATH, strlen(ICMPD_PATH));

    Connect(icmpfd, (SA *) &sun, sizeof(sun));

    Write_fd(icmpfd, (void *)"1", 1, sockfd);

    char recvline[MAXLINE+1], sendline[MAXLINE];
    ssize_t n = Read(icmpfd, recvline, 1);

    if (n != 1 || recvline[0] != '1') {
        err_quit("error creating icmp socket, n = %d, char = %c", n, recvline[0]);
    }

    int maxfdp1;
    fd_set rset;
    struct timeval tv;
    struct icmpd_err icmpd_err;

    FD_ZERO(&rset);
    maxfdp1 = max(sockfd, icmpfd) + 1;

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        tv.tv_sec = 5;
        tv.tv_usec = 0;

        FD_SET(sockfd, &rset);
        FD_SET(icmpfd, &rset);

        if ((n = Select(maxfdp1, &rset, NULL, NULL, &tv)) == 0) {
            fprintf(stderr, "socket timeout\n");
            continue;
        }

        if (FD_ISSET(sockfd, &rset)) {
            n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
            recvline[n] = 0;
            Fputs(recvline, stdout);
        }

        if (FD_ISSET(icmpfd, &rset)) {
            if ((n = Read(icmpfd, &icmpd_err, sizeof(icmpd_err))) == 0) {
                err_quit("ICMP daemon terminated");
            } else if (n != sizeof(icmpd_err)) {
                err_quit("n = %d, expected %d", n, sizeof(icmpd_err));
            }

            printf("ICMP error: dest = %s, %s, type = %d, code = %d\n",
                    Sock_ntop((SA *)&icmpd_err.icmpd_dest, icmpd_err.icmpd_len),
                    strerror(icmpd_err.icmpd_errno),
                    icmpd_err.icmpd_type,
                    icmpd_err.icmpd_code);
        }
    }
}

int
main(int argc, char **argv)
{
    int                 sockfd;
    socklen_t           salen;
    struct sockaddr     *sa;

    if (argc != 3)
        err_quit("usage: udpcli01 <hostname> <service>");

    sockfd = Udp_client(argv[1], argv[2], &sa, &salen);

    dg_cli(stdin, sockfd, sa, salen);

    exit(0);
}

