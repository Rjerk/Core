#include "../../unp.h"

int main(int argc, char** argv)
{
    int listenfd = -1;
    socklen_t addrlen = 0;
    if (argc == 2) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else if (argc == 3) {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    } else {
        err_quit("usage: ./server [ <host> ] <port#>");
    }

    void sig_chld(int), sig_int(int), web_child(int);
    struct sockaddr* clntaddr = (SA *) Malloc (addrlen);

    Signal(SIGCHLD, sig_chld);
    Signal(SIGINT, sig_int);

    int connfd;
    pid_t childpid;
    socklen_t clntlen;
    for ( ; ; ) {
        clntlen = addrlen;
        if ((connfd = accept(listenfd, clntaddr, &clntlen)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                err_sys("accept error");
            }
        }

        if ((childpid = Fork()) == 0) {
            Close(listenfd);
            web_child(connfd);
            exit(0);
        }
        Close(connfd);
    }
}

void sig_int(int)
{
    void pr_cpu_time(void);
    pr_cpu_time();
    exit(0);
}
