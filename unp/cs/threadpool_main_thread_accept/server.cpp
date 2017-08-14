#include "../../unp.h"
#include "../../unpthread.h"
#include "pthread.h"

static int nthreads;

int main(int argc, char** argv)
{
    int listenfd = -1;
    socklen_t addrlen = 0;

    if (argc == 3) {
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    } else if (argc == 4) {
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    } else {
        err_quit("usage: ./server [ <host> ] <port#> <#threads>");
    }

    void sig_int(int), thread_make(int);

    struct sockaddr* clntaddr =  (SA *) Malloc (addrlen);
    nthreads = atoi(argv[argc-1]);

    tptr = (Thread *) Calloc (nthreads, sizeof(Thread));
    iget = iput = 0;

    for (int i = 0; i < nthreads; ++i) {
        thread_make(i); //  only main thread returns.
    }

    Signal(SIGINT, sig_int);

    socklen_t clntlen;
    int connfd;


    for ( ; ; ) {
        clntlen = addrlen;
        connfd = Accept(listenfd, clntaddr, &clntlen);

        Pthread_mutex_lock(&clifd_mutex);

        clifd[iput] = connfd;
        if (++iput == MAXNCLI) {
            iput = 0;
        }
        if (iput == iget) {
            err_quit("iput = iget == %d", iput);
        }

        Pthread_cond_signal(&clifd_cond);
        Pthread_mutex_unlock(&clifd_mutex);
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
    void web_child(int);

    printf("thread %d starting\n", *((int*)arg));
    for ( ; ; ) {
        Pthread_mutex_lock(&clifd_mutex);

        while (iget == iput) {
            Pthread_cond_wait(&clifd_cond, &clifd_mutex);
        }
        connfd = clifd[iget];
        if (++iget == MAXNCLI) {
            iget = 0;
        }

        Pthread_mutex_unlock(&clifd_mutex);

        ++tptr[*((int*)arg)].thread_count;
        web_child(connfd);
        Close(connfd);
    }
}
