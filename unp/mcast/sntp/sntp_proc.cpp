#include "sntp.h"

void sntp_proc(char* buf, ssize_t n, struct timeval* nowptr)
{
    if (n < (ssize_t)sizeof(struct ntpdata)) {
        printf("\npacket too small: %ld bytes\n", n);
        return ;
    }

    struct ntpdata* ntp = (struct ntpdata *) buf;
    int version = (ntp->status & VERSION_MASK) >> 3;
    int mode = ntp->status & MODE_MASK;
    printf("\nv%d, mode %d, strat %d, ", version, mode, ntp->stratum);
    if (mode == MODE_CLIENT) {
        printf("client\n");
        return ;
    }

    int32_t nsec = ntohl(ntp->xmt.int_part) - JAN_1970;
    double useci = ntohl(ntp->xmt.fraction);
    double usecf = useci / 4294967296.0; // divide by 2**32 -> [0. 1.0].
    useci = usecf * 1000000.0; // fraction -> parts per million.

    struct timeval diff;
    diff.tv_sec = nowptr->tv_sec - nsec;
    if ((diff.tv_usec = nowptr->tv_usec - useci) < 0) {
        diff.tv_usec += 1000000;
        --diff.tv_sec;
    }

    useci = (diff.tv_sec * 1000000) + diff.tv_usec; // diff in microsec.
    printf("clock difference = %f usec\n", useci);


}
