#ifndef PTHREAD_H
#define PTHREAD_H

#include <pthread.h>
#include <sys/socket.h>

using Thread = struct {
    pthread_t tid;
    long thread_count;
};

Thread* tptr = nullptr;

int listenfd = -1, nthreads = 0;

socklen_t addrlen = 0;

pthread_mutex_t mlock_ = PTHREAD_MUTEX_INITIALIZER;

#endif
