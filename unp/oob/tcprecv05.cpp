#include "../unp.h"

int listenfd = -1;
int connfd = -1;

void sig_urg(int)
{
    printf("SIGURG received.\n");
    char buf[2048];
    int n = Recv(connfd, buf, sizeof(buf)-1, MSG_OOB);
    buf[n] = 0;
    printf("read %d OOB byte\n", n);
}

int main(int argc, char** argv)
{
    int listenfd = -1;
    if (argc == 2) {
        listenfd = Tcp_listen(NULL, argv[1], NULL);
    } else if (argc == 3) {
        listenfd = Tcp_listen(argv[1], argv[2], NULL);
    } else {
        err_quit("usage: ./tcprecv05 [ <host> ] [ <port#> ]");
    }

    const int size = 4096;
    Setsockopt(listenfd, SOL_SOCKET, SO_OOBINLINE, &size, sizeof(size));

    int connfd = Accept(listenfd, NULL, NULL);

    Signal(SIGURG, sig_urg);
    Fcntl(connfd, F_SETOWN, getpid());

    for ( ; ; ) {
        pause();
    }
}
