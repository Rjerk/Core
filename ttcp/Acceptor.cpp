#include "Acceptor.h"
#include "TcpStream.h"

#include <cstdio>
#include <sys/socket.h>

Acceptor::Acceptor(const InetAddress& listen_addr)
    : listen_sock(Socket::createTCP())
{
    listen_sock.setReuseAddr(true);
    listen_sock.bindOrDie(listen_addr);
    listen_sock.listenOrDie();
}

TcpStreamPtr Acceptor::accept()
{
    // FIXME: use accept4
    int sockfd = ::accept(listen_sock.fd(), NULL, NULL);
    if (sockfd >= 0) {
        return TcpStreamPtr(new TcpStream(Socket(sockfd)));
    } else {
        perror("Acceptor::accept");
        return TcpStreamPtr();
    }
}
