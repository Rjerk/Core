#ifndef THREAD_H
#define THREAD_H

#include "atomic.h"

#include <functional>
#include <pthread.h>
#include <memory>

class Thread : noncopyable {
public:
    using ThreadFunc = std::function<void ()>;
    explicit Thread(const ThreadFunc&, const std::string& name = std::string());
    ~Thread();

    void start();
    void join();

    bool started() const { return started_; }
    pthread_t pthreadId() const { return pthreadId_; }
    pid_t tid() const { return *tid_; }
    const std::string& name() const { return name_; }

    static int numCreated() { return numCreated_.get(); }

private:
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    std::shared_ptr<pid_t> tid_;
    ThreadFunc func_;
    std::string name_;

    static AtomicInt32 numCreated_;
};

namespace CurrentThread {
    pid_t tid();
    const char* name();
    bool isMainThread();
};

#endif
