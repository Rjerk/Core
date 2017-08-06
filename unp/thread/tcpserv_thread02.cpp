#include "unpthread.h"

static void* doit(void* arg)
{
    int connfd = *((int *) arg);
    free(arg);

    Pthread_detach(pthread_self());
    str_echo(connfd);
    Close(connfd);
    return NULL;
}


int main(int argc, char** argv)
{
    int listenfd = -1;
    pthread_t tid;
    socklen_t addrlen = 0, len = 0;

    if (argc == 2) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else if (argc == 3) {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    } else {
        err_quit("usage: ./serv [ <host> ] <service or port>");
    }

    struct sockaddr* clntaddr = (struct sockaddr *) Malloc (addrlen);

    int* iptr = NULL;
    for ( ; ; ) {
        len = addrlen;
        iptr = (int *) Malloc (sizeof(int));
        *iptr = Accept(listenfd, clntaddr, &len);
        Pthread_create(&tid, NULL, &doit, iptr);
    }
}
