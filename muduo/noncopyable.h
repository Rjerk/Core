#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H

class noncopyable {
private:
    noncopyable() = default;
    ~noncopyable() = default;
protectedd:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
};

#endif NON_COPYABLE_H
