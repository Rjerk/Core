#include "unp.h"

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];

    for ( ; ; ) {
        while ((n = Read(sockfd, buf, MAXLINE)) > 0) {
            Writen(sockfd, buf, n);
        }

        if (n < 0 && errno == EINTR) {
            continue;
        } else if (n == 0) {
            break;
        } else if (n < 0) {
            err_sys("str_echo: read error");
        }
    }
}
