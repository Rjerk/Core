#ifndef UNP_ICMP_H
#define UNP_ICMP_H

#include "../../unp.h"

#define ICMPD_PATH "/tmp/icmpd"

struct icmpd_err {
    int icmpd_errno; // EHOSTUNREACH, EMSGSIZE, ENONNREFUSED.
    char icmpd_type; // actual ICMPv[46] type.
    char icmpd_code; // actual ICMPv[46] code.
    socklen_t icmpd_len; // lenght of sockaddr{} that follows;
    struct sockaddr_storage icmpd_dest; // sockaddr_strorage handles any size.
};



#endif
