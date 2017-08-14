#include "../unp.h"

#define MAXN 16384 // max # bytes to request from server.

int main(int argc, char** argv)
{
    if (argc != 6) {
        err_quit("usage: ./client <hostname or IPaddr> <port> <#children> "
                 "<#loops/child> <#bytes/request>");
    }

    int fd;
    pid_t pid;
    ssize_t n;
    char request[MAXLINE], reply[MAXN];

    int nchildren = atoi(argv[3]);
    int nloops = atoi(argv[4]);
    int nbytes = atoi(argv[5]);
    snprintf(request, sizeof(request), "%d\n", nbytes); // newline at end.

    for (int i = 0; i < nchildren; ++i) {
        if ((pid = Fork()) == 0) {
            for (int j = 0; j < nloops; ++j) {
                fd = Tcp_connect(argv[1], argv[2]);

                Write(fd, request, strlen(request));

                if ((n = Readn(fd, reply, nbytes)) != nbytes) {
                    err_quit("server returned %d bytes", n);
                }

                Close(fd); // TIME_WAIT on client, on server.
            }
            printf("child %d done\n", i);
            exit(0);
        }
    }

    while (wait(NULL) > 0) ;

    if (errno != ECHILD) {
        err_sys("wait error");
    }

    exit(0);
}


