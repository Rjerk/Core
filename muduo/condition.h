#ifndef CONDITION_H
#define CONDITION_H

#include "mutex.h"

class Condition {
public:
    explicit Condition(MutexLock& mutex):
        mutex_(mutex)
    {
        pthread_cond_init(&pcond, NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&pcond);
    }
    void wait()
    {
        pthread_cond_wait(&pcond_, mutex_.getPhreadMutex());
    }
    void notify()
    {
        pthread_cond_signal(&pcond_);
    }
    void notifyAll()
    {
        pthread_cond_broadcast(&pcond_);
    }
private:
    pthread_cond_t pcond_;
    MutexLock& mutex_;
};

#endif CONDITION_H