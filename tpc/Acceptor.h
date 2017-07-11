#pragma once

#include "Common.h"
#include "Socket.h"

#include <memory>

class InetAddress;

class TcpStream;
using TcpStreamPtr = std::unique_ptr<TcpStream>;

class Acceptor : noncopyable {
public:
    explicit Acceptor(const InetAddress& listen_addr);
    ~Acceptor() = default;
    Acceptor(Acceptor&&) = default;
    Acceptor& operator=(Acceptor&&) = default;

    // thread safe.
    TcpStreamPtr accept();

private:
    Socket listen_sock;
};
