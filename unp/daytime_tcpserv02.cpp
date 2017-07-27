#include "unp.h"

int main(int argc, char** argv)
{
    int listenfd = -1;

    socklen_t addrlen;
    if (argc == 2) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else if (argc == 3) {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    } else {
        err_quit("usage ./daytime_tcpserv <service/port>");
    }

    socklen_t len;
    int connfd;
    time_t ticks;
    char buff[MAXLINE];
    struct sockaddr_storage clntaddr;
    for ( ; ; ) {
        len = sizeof(clntaddr);
        connfd = Accept(listenfd, (SA *) &clntaddr, &len);
        printf("connection from %s\n", Sock_ntop((SA *) &clntaddr, len));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, sizeof(buff));

        Close(connfd);
    }
}
