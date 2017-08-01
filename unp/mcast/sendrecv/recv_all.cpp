#include "../../unp.h"

void recv_all(int recvfd, socklen_t salen)
{
    int n;
    char line[MAXLINE];
    socklen_t len;
    struct sockaddr* safrom = (struct sockaddr *) Malloc (salen);

    for ( ; ; ) {
        len = salen;
        n = Recvfrom(recvfd, line, MAXLINE, 0, safrom, &len);
        line[n] = 0;
        printf("from %s: %s", Sock_ntop(safrom, len), line);
    }
}
