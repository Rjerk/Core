#include "../../unp.h"
#include "child.h"

static int nchildren;

int main(int argc, char** argv)
{
    int listenfd = -1;
    socklen_t addrlen;

    if (argc == 3) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else if (argc == 4) {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    } else {
        err_quit("usage: ./server [ <host> ] <port#> <#children>");
    }

    void sig_int(int);
    pid_t child_make(int, int, int);

    fd_set rset, masterset;
    FD_ZERO(&masterset);
    FD_SET(listenfd, &masterset);
    int maxfd = listenfd, nsel, connfd, rc;
    ssize_t n;
    socklen_t clntlen;

    struct sockaddr* clntaddr = (SA *) Malloc (addrlen);
    nchildren = atoi(argv[argc-1]);
    int navail = nchildren;

    cptr = (Child *) Calloc (nchildren, sizeof(Child));

    for (int i = 0; i < nchildren; ++i) {
        child_make(i, listenfd, addrlen); // parent returns.
        FD_SET(cptr[i].child_pipefd, &masterset);
        maxfd = max(maxfd, cptr[i].child_pipefd);
    }

    Signal(SIGINT, sig_int);

    for ( ; ; ) {
        rset = masterset;
        if (navail <= 0) {
            FD_CLR(listenfd, &rset); // turn off if no available children.
        }

        nsel = Select(maxfd+1, &rset, NULL, NULL, NULL);

        int i;

        if (FD_ISSET(listenfd, &rset)) {
            clntlen = addrlen;
            connfd = Accept(listenfd, clntaddr, &clntlen);

            for (i = 0; i < nchildren; ++i) {
                if (cptr[i].child_status == 0) {
                    break; // available.
                }
            }

            if (i == nchildren) {
                err_quit("no available children");
            }

            cptr[i].child_status = 1;
            ++cptr[i].child_count; // mark child as busy.
            --navail;

            n = Write_fd(cptr[i].child_pipefd, (void *) "", 1, connfd);
            Close(connfd);

            if (--nsel == 0) {
                continue; // all done with select() results.
            }
        }

        for (i = 0; i < nchildren; ++i) {
            if (FD_ISSET(cptr[i].child_pipefd, &rset)) {
                if ((n = Read(cptr[i].child_pipefd, &rc, 1)) == 0) {
                    err_quit("child %d terminated unexpectedly", i);
                }
                cptr[i].child_status = 0;
                ++navail;
                if (--nsel == 0) {
                    break; // all done with select() results.
                }
            }
        }
    }
}
