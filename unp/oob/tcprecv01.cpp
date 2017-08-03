#include "../unp.h"

int listenfd = -1;
int connfd = -1;

void sig_urg(int)
{
    printf("SIGURG received.\n");
    char buf[MAXLINE];
    int n = Recv(connfd, buf, sizeof(buf)-1, MSG_OOB);
    buf[n] = 0;
    printf("read %d OOB byte: %s\n", n, buf);
}

int main(int argc, char** argv)
{
    if (argc == 2) {
        listenfd = Tcp_listen(NULL, argv[1], NULL);
    } else if (argc == 3) {
        listenfd = Tcp_listen(argv[1], argv[2], NULL);
    } else {
        err_quit("usage: ./tcprecv01 [ <host> ] [ <port#> ]");
    }

    connfd = accept(listenfd, NULL, NULL);
    Signal(SIGURG, sig_urg);
    Fcntl(connfd, F_SETOWN, getpid());

    int n;
    char buf[MAXLINE];
    for ( ; ; ) {
        if ((n = Read(connfd, buf, sizeof(buf)-1)) == 0) {
            printf("received EOF\n");
            exit(0);
        }
        buf[n] = 0;
        printf("read %d bytes: %s\n", n, buf);
    }
}
