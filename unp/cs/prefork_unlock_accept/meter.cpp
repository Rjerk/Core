#include "../../unp.h"
#include <sys/mman.h>

long* meter(int nchildren)
{
    int fd = -1;
    long* ptr;

#ifdef MAP_ANON
    ptr = (long *) Mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE,
                    MAP_ANON | MAP_SHARED, -1, 0);
#else
    fd = Open("/dev/zero", O_RDWR, 0);
    ptr = (long *) Mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE,
                    MAP_SHARED, fd, 0);
    Close(fd);
#endif
    return ptr;
}
