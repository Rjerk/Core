#include "../../unp.h"

static int nchildren;
static pid_t* pids;

int main(int argc, char** argv)
{
    int listenfd = -1;
    socklen_t addrlen;
    if(argc == 3) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else if (argc == 4) {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    } else {
        err_quit("usage: ./server [ <host> ] <port#> <#children>");
    }

    void sig_int(int);
    pid_t child_make(int, int, int);

    nchildren = atoi(argv[argc-1]);
    pids = (pid_t *) Calloc (nchildren, sizeof(pid_t));

    for (int i = 0; i < nchildren; ++i) {
        pids[i] = child_make(i, listenfd, addrlen); // parent returns.
    }

    Signal(SIGINT, sig_int);
}

void sig_int(int)
{
    void pr_cpu_time(void);

    for (int i = 0; i < nchildren; ++i) {
        kill(pids[i], SIGTERM);
    }

    while (wait(NULL) > 0) ; // wait for all children.

    if (errno != ECHILD) {
        err_sys("wait error");
    }

    pr_cpu_time();

    exit(0);
}
