#pragma once

#include "Common.h"
#include <utility>

class InetAddress;

class Socket : noncopyable {
public:
    explicit Socket(int sockfd_);
    ~Socket();

    Socket(Socket&& rhs)
        : Socket(rhs.sockfd)
    {
        rhs.sockfd = -1;
    }

    Socket& operator=(Socket&& rhs)
    {
        swap(rhs);
        return *this;
    }

    void swap(Socket& rhs)
    {
        std::swap(sockfd, rhs.sockfd);
    }

    int fd() { return sockfd; }

    // Socket API
    void bindOrDie(const InetAddress& addr);
    void listenOrDie();
    // return on on success
    int connect(const InetAddress& addr);
    void shutdownWrite();

    void setReuseAddr(bool on);
    void setTcpNoDelay(bool on);

    InetAddress getLocalAddr() const;
    InetAddress getPeerAddr() const;

    int read(void* buf, int len);
    int write(const void* buf, int len);

    // factory method
    static Socket createTCP();
    static Socket createUDP();
private:
    int sockfd;
};
