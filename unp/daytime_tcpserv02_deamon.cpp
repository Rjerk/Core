#include "unp.h"

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 3) {
        err_quit("usage: ./daytime_tcpserv02_deamon [ <host> ] <service/port>");
    }

    daemon_init(argv[1], 0);

    int listenfd = -1;
    socklen_t addrlen;
    if (argc == 2) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    }

    socklen_t len;
    int connfd;
    time_t ticks;
    char buff[MAXLINE];
    struct sockaddr_storage clntaddr;
    for ( ; ; ) {
        len = sizeof(clntaddr);
        connfd = Accept(listenfd, (SA *) &clntaddr, &len);
        err_msg("connection from %s\n", Sock_ntop((SA *) &clntaddr, len));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, sizeof(buff));

        Close(connfd);
    }
}
