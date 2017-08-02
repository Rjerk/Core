#include "../unp.h"
#include <sys/param.h>

ssize_t recvfrom_flags(int fd, void* ptr, size_t nbytes, int* flagsp,
                    SA* sa, socklen_t* salenptr, struct unp_in_pktinfo* pktp)
{
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(struct in_addr))
                   + CMSG_SPACE(sizeof(struct unp_in_pktinfo))];
    } control_un;

    struct msghdr msg;
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    msg.msg_flags = 0;
    msg.msg_name = sa;
    msg.msg_namelen = *salenptr;

    struct iovec iov[1];
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;

    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    ssize_t n;
    if ((n = recvmsg(fd, &msg, *flagsp)) < 0) {
        return n;
    }

    *salenptr = msg.msg_namelen;
    if (pktp) {
        bzero(pktp, sizeof(struct unp_in_pktinfo)); // 0.0.0.0, i/f = 0
    }

    *flagsp = 0;
    return n;
}

ssize_t Recvfrom_flags(int fd, void* ptr, size_t nbytes, int* flagsp,
                        SA* sa, socklen_t* salenptr,  struct unp_in_pktinfo* pktinfo)
{
    return recvfrom_flags(fd, ptr, nbytes, flagsp, sa, salenptr, pktinfo);
}
