#ifndef ATOMIC_H
#define ATOMIC_H

#include "noncopyable.h"
#include <cstdint>

template <typename T>
class AtomicIntegerT: noncopyable {
public:
    AtomicIntegerT()
        : value_(0)
    {
    }

    T get() const
    {
        return __sync_val_compare_and_swap(const_cast<volatile T*>(&value_), 0, 0);
    }

    T getAndAdd(T x)
    {
        return __sync_fetch_and_add(&value_, x);
    }

    T addAndGet(T x)
    {
        return getAndAdd(x) + x;
    }

    T incrementAndGet()
    {
        return addAndGet(1);
    }

    void add(T x)
    {
        getAndAdd(x);
    }

    void increment()
    {
        incrementAndGet();
    }

    void decrement()
    {
        getAndAdd(-1);
    }

    T getAndSet(T new_val)
    {
        return __sync_lock_test_and_set(&value_, new_val);
    }
private:
    volatile T value_;
};

using AtomicInt32 = AtomicIntegerT<int32_t>;
using AtomicInt64 = AtomicIntegerT<int64_t>;

#endif
