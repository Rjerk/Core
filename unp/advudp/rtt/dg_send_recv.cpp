#include "unprtt.h"
#include <setjmp.h>

#define RTT_DEBUG

static struct rtt_info rttinfo;
static int rttinit = 0;
static struct msghdr msgsend, msgrecv;
static struct hdr {
    uint32_t seq; // sequence.
    uint32_t ts; // timestamp when sent.
} sendhdr, recvhdr;

static void sig_alrm(int signo);
static sigjmp_buf jmpbuf;

ssize_t dg_send_recv(int fd, const void* outbuff, size_t outbytes,
                    void* inbuff, size_t inbytes,
                    const SA* destaddr, socklen_t destlen)
{
    if (rttinit == 0) {
        rtt_init(&rttinfo); // first time we're called.
        rttinit = 1;
        rtt_d_flag = 1;
    }

    ++sendhdr.seq;

    struct iovec iovsend[2], iovrecv[2];
    msgsend.msg_name = (void *) destaddr;
    msgsend.msg_namelen = destlen;
    msgsend.msg_iov = iovsend;
    msgsend.msg_iovlen = 2;
    iovsend[0].iov_base = &sendhdr;
    iovsend[0].iov_len = sizeof(struct hdr);
    iovsend[0].iov_base = (void*) outbuff;
    iovsend[0].iov_len = outbytes;

    msgrecv.msg_name = NULL;
    msgrecv.msg_namelen = 0;
    msgrecv.msg_iov = iovrecv;
    msgrecv.msg_iovlen = 2;
    iovrecv[0].iov_base = &recvhdr;
    iovrecv[0].iov_len = sizeof(struct hdr);
    iovrecv[0].iov_base = inbuff;
    iovrecv[0].iov_len = inbytes;

    Signal(SIGALRM, sig_alrm);
    rtt_newpack(&rttinfo); // initialize for this packet.

    ssize_t n;

sendagain:
    sendhdr.ts = rtt_ts(&rttinfo);
    Sendmsg(fd, &msgsend, 0);

    alarm(rtt_start(&rttinfo)); // cal timeout value & start timer.

    if (sigsetjmp(jmpbuf, 1) != 0) {
        if (rtt_timeout(&rttinfo) < 0) {
            err_msg("do_send_recv: no respond from server, giving up");
            rttinit = 0; // reinit in case we're called again.
            errno = ETIMEDOUT;
            return -1;
        }
        goto sendagain;
    }

    do {
        n = Recvmsg(fd, &msgrecv, 0);
    } while (n < (ssize_t) sizeof(struct hdr) || recvhdr.seq != sendhdr.seq);

    alarm(0); // stop SIGALRM timer.

    // calculate & store new RTT estimator value.
    rtt_stop(&rttinfo, rtt_ts(&rttinfo) - recvhdr.ts);
}

ssize_t Dg_send_recv(int fd, const void* outbuff, size_t outsize,
                            void* inbuff, size_t inbytes,
                                                const SA* destaddr, socklen_t destlen)
{
    return dg_send_recv(fd, outbuff, outsize, inbuff, inbytes, destaddr, destlen);
}



