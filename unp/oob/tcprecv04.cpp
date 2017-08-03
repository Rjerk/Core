#include "../unp.h"

int main(int argc, char** argv)
{
    int listenfd = -1;
    if (argc == 2) {
        listenfd = Tcp_listen(NULL, argv[1], NULL);
    } else if (argc == 3) {
        listenfd = Tcp_listen(argv[1], argv[2], NULL);
    } else {
        err_quit("usage: ./tcprecv04 [ <host> ] [ <port#> ]");
    }

    const int on = 1;
    Setsockopt(listenfd, SOL_SOCKET, SO_OOBINLINE, &on, sizeof(on));

    int connfd = Accept(listenfd, NULL, NULL);
    sleep(5);

    int n;
    char buf[MAXLINE];
    for ( ; ; ) {
        if (Sockatmark(connfd)) {
            printf("at OOB mark\n");
        }

        if ((n = Read(connfd, buf, sizeof(buf)-1)) == 0) {
            printf("received EOF\n");
            exit(0);
        }
        buf[n] = 0;
        printf("read %d bytes: %s\n", n, buf);
    }
}
