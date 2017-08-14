#include "../../unpthread.h"
#include "pthread.h"

int main(int argc, char** argv)
{
    if (argc == 3) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else if (argc == 4) {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    } else {
        err_quit("usage: ./server [ <host> ] <port#> <#threads>");
    }

    void sig_int(int), thread_make(int);

    nthreads = atoi(argv[argc-1]);

    tptr = (Thread *) Calloc (nthreads, sizeof(Thread));

    for (int i = 0; i < nthreads; ++i) {
        thread_make(i); //  only main thread returns.
    }

    Signal(SIGINT, sig_int);

    for ( ; ; ) {
        pause(); // everything done by threads.
    }
}

void thread_make(int i)
{
    void* thread_main(void *);

    Pthread_create(&tptr[i].tid, NULL, &thread_main, (void *) &i);
    return ;
}

void* thread_main(void* arg)
{
    int connfd;
    socklen_t clntlen;
    struct sockaddr* clntaddr = (SA *) Malloc (addrlen);

    void web_child(int);

    printf("thread %d starting\n", *((int*)arg));
    for ( ; ; ) {
        clntlen = addrlen;
        Pthread_mutex_lock(&mlock_);
        connfd = Accept(listenfd, clntaddr, &clntlen);

        Pthread_mutex_unlock(&mlock_);

        ++tptr[*((int*)arg)].thread_count;
        web_child(connfd);
        Close(connfd);
    }
}
