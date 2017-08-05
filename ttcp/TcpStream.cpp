#include "TcpStream.h"
#include "InetAddress.h"

#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

namespace {

class IgnoreSigPipe {
public:
    IgnoreSigPipe()
    {
        ::signal(SIGPIPE, SIG_IGN);
    }
} initObj;

bool isSelfConnection(const Socket& sock)
{
    return sock.getLocalAddr() == sock.getPeerAddr();
}

}

TcpStream::TcpStream(Socket&& sock_)
    : sock(std::move(sock_))
{
}

int TcpStream::receiveAll(void* buf, int len)
{
    // FIXME: EINTR
    return ::recv(sock.fd(), buf, len, MSG_WAITALL);
}

int TcpStream::receiveSome(void* buf, int len)
{
    // FIXME: EINTR
    return sock.read(buf, len);
}

int TcpStream::sendAll(const void* buf, int len)
{
    int written = 0;
    while (written < len) {
        int nw = sock.write(static_cast<const char*>(buf)+written, len-written);
        if (nw > 0) {
            written += nw;
        } else if (nw == 0) {
            break;
        } else if (errno != EINTR) {
            break;
        }
    }
    return written;
}

int TcpStream::sendSome(const void* buf, int len)
{
    // FIXME: EINTR
    return sock.write(buf, len);
}

void TcpStream::setTcpNoDelay(bool on)
{
    sock.setTcpNoDelay(on);
}

void TcpStream::shutdownWrite()
{
    sock.shutdownWrite();
}

TcpStreamPtr TcpStream::connect(const InetAddress& serverAddr)
{
    return connectInternal(serverAddr, nullptr);
}

TcpStreamPtr TcpStream::connect(const InetAddress& serverAddr, const InetAddress& localAddr)
{
    return connectInternal(serverAddr, &localAddr);
}

TcpStreamPtr TcpStream::connectInternal(const InetAddress& serverAddr, const InetAddress* localAddr)
{
    TcpStreamPtr stream;
    Socket sockfd(Socket::createTCP());
    if (localAddr) {
        sockfd.bindOrDie(*localAddr);
    }
    if (sockfd.connect(serverAddr) == 0 && !isSelfConnection(sockfd)) {
        // FIXME: do poll(POLLOUT) to check errors.
        stream.reset(new TcpStream(std::move(sockfd)));
    }
    return stream;
}
