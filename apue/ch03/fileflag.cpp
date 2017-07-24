#include "../apue.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        err_quit("usage: ./fileflag <descriptor#>");
    }

    int flag;
    if ((flag = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        err_sys("fcntl error for fd %d", atoi(argv[1]));
    }

    switch (flag & O_ACCMODE) {
        case O_RDONLY:
            printf ("read only");
            break;
        case O_WRONLY:
            printf ("write only");
            break;
        case O_RDWR:
            printf ("read write");
            break;
        default:
            err_dump("unknown access mode");
    }

    if (flag & O_APPEND) {
        printf (", append");
    }
    if (flag & O_NONBLOCK) {
        printf (", nonblocking");
    }
    if (flag & O_SYNC) {
        printf (", synchronous writes");
    }

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC) {
        printf (", synchronous writes");
    }
#endif

    putchar('\n');
    exit(0);
}
