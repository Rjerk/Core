#ifndef UTILITY_H
#define UTILITY_H

#include <sys/types.h>

namespace fdutils {

void setNonblock(int fd);

void setCloexec(int fd);

ssize_t write(int fd, const void* buf, size_t count);

void close(int fd);

}

#endif
