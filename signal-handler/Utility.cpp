#include "Utility.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

namespace fdutils {

void setNonblock(int fd)
{
    int flags = ::fcntl(fd, F_GETFL);
    if (::fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        ::close(fd);
        throw std::runtime_error{"Cannnot set O_NONBLOCK"};
    }
}

void setCloexec(int fd)
{
    int flags = ::fcntl(fd, F_GETFL);
    if (::fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0) {
        close(fd);
        throw std::runtime_error{"Cannot set FD_CLOEXEC"};
    }
}

ssize_t write(int fd, const void* buf, size_t count)
{
    ssize_t n;
    if ((n = ::write(fd, buf, count)) == -1) {
        throw std::runtime_error{"write() error"};
    }
    return n;
}

void close(int fd)
{
    if (fd >= 0) {
        if (::close(fd) == -1) {
            throw std::runtime_error{"close() error"};
        }
    }
}

}

