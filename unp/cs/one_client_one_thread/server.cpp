#include "../../unpthread.h"

static void* doit(void* arg)
{
    void web_child(int);

    Pthread_detach(pthread_self());
    web_child(*((int*)arg));
    Close(*((int*) arg));
    return NULL;
}


int main(int argc, char** argv)
{
    int listenfd = -1, connfd = -1;
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

    for ( ; ; ) {
        len = addrlen;
        connfd = Accept(listenfd, clntaddr, &len);
        Pthread_create(&tid, NULL, &doit, (void *) &connfd);
    }
}
