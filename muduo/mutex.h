#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#inclue "noncopyable.h"
#include "current_thread.h"
#include <pthread.h>
#include <assert.h>

class MutexLock: noncopyable {
public:
	MutexLock(): holder_(0)
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~MutexLock()
	{
		assert(holder_ == 0);
		pthread_mutex_destroy(&mutex_);
	}
	bool isLockedByThisThread()
    {
        return holder_ == CurrentThread::tid();
    }
    void assertLocked()
    {
        assert(isLockedByThisThread());
    }
    void lock() // used by MutexLockGuard, not for user.
    {
        pthread_mutex_lock(&mutex_);
        holder_ = CurrentThread::tid();
    }
    void unlock() // used by MutexLockGuard, not for user.
    {
        holder_ = 0;
        pthread_mutex_unlock(&mutex_);
    }
    pthread_mutex_t* getPthreadMutex() // used by Condition, not for user.
    {
        return &mutex_;
    }
private:
	pthread_mutex_t mutex_;
	pid_t holder_;
};

class MutexLockGuard : noncopyable {
public:
    explicit MutexLockGuard(MutexLock& mutex):
        mutex_(mutex)
    {
        mutex_.lock();
    }
    ~MutexLockGuard()
    {
        mutex_.unlock();
    }
private:
    MutexLock& mutex_;
};

#define MutexLockGuard(x) static_assert(false, "missing mutex guard var name.")

#endif MUTEX_LOCK_H
