#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

using Thread = struct {
    pthread_t tid;
    long thread_count;
};

Thread* tptr = nullptr;

#define MAXNCLI 32

int clifd[MAXNCLI], iget, iput;

pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond =  PTHREAD_COND_INITIALIZER;
#endif
