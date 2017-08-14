#include "../../unp.h"

pid_t child_make(int i, int listenfd, int addrlen)
{
    void child_main(int, int, int);

    pid_t pid;
    if ((pid = Fork()) > 0) {
        return pid;
    }

    child_main(i, listenfd, addrlen); // never returns.

    return -1; // never run here.
}

void child_main(int, int listenfd, int addrlen)
{
    void web_child(int);
    int connfd;
    socklen_t clntlen;
    struct sockaddr* clntaddr = (SA *) Malloc (addrlen);

    printf("child %ld starting\n", (long) getpid());

    // make select collision.
    fd_set rset;
    FD_ZERO(&rset);
    for ( ; ; ) {
        FD_SET(listenfd, &rset);
        Select(listenfd+1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(listenfd, &rset) == 0) {
            err_quit("listenfd readable");
        }

        clntlen = addrlen;
        connfd = Accept(listenfd, clntaddr, &clntlen);
        web_child(connfd);
        Close(connfd);
    }

}
