#include "unp.h"

int readable_timeo(int fd, int sec)
{
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);

    struct timeval tv;
    tv.tv_sec = sec;
    tv.tv_usec = 0;

    return (select(fd+1, &rset, NULL, NULL, &tv));
}

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    char sendline[MAXLINE], recvline[MAXLINE+1];
    while ((Fgets(sendline, MAXLINE, fp)) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        if (readable_timeo(sockfd, 5) == 0) {
            fprintf(stderr, "socket timeout\n");
        } else {
            int n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
            recvline[n] = 0;
            Fputs(recvline, stdout);
        }
    }
}
