#include "unp.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage ./daytime_tcpserv <service/port>");
    }

    int listenfd = Tcp_listen(NULL, argv[1], NULL);

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
