#include "../unp.h"

#include <netinet/in_systm.h>
#include <netinet/ip.h>

static u_char* optr; // pointer into options being formed.
static u_char* lenptr; // pointer to length bytes in SRR options.
static int ocnt; // count of # address.

u_char* inet_srcrt_init(int type)
{
    optr = (u_char *) Malloc (44); // NOP, code, len, ptr, up to 10 addresses.
    bzero(optr, 44); // guarantees EOLs at end.
    ocnt = 0;
    *optr++ = IPOPT_NOP;
    *optr++ = type ? IPOPT_SSRR : IPOPT_LSRR;
    lenptr = optr++; // fill in length later.
    *optr++ = 4; // offset to first address.

    return optr - 4;
}

int inet_srcrt_add(char* hostptr)
{
    if (ocnt > 9) {
        err_quit("too many source routes with: %s", hostptr);
    }

    struct addrinfo* ai = Host_serv(hostptr, NULL, AF_INET, 0);
    struct sockaddr_in* sin = (struct sockaddr_in *) ai->ai_addr;
    memcpy(optr, &sin->sin_addr, sizeof(struct in_addr));
    freeaddrinfo(ai);

    optr += sizeof(struct in_addr);
    ++ocnt;
    int len = 3 + (ocnt * sizeof(struct in_addr));
    *lenptr = len;
    return len + 1;
}

void inet_srcrt_print(u_char* ptr, int len)
{
    struct in_addr hop1;
    memcpy(&hop1, ptr, sizeof(struct in_addr));
    ptr += sizeof(struct in_addr);

    u_char c;
    while ((c = *ptr++) == IPOPT_NOP) { // skip any leading NOL.
        ;
    }

    if (c == IPOPT_LSRR) {
        printf("received LSRR: ");
    } else if (c == IPOPT_SSRR) {
        printf("received SSRR: ");
    } else {
        printf("received option type %d\n", c);
    }

    char str[INET_ADDRSTRLEN];
    printf("%s ", Inet_ntop(AF_INET, &hop1, str, sizeof(str)));

    len = *ptr++ - sizeof(struct in_addr); // substract dest IP addr.
    ++ptr; // skil over pointer.

    while (len > 0) {
        printf("%s ", Inet_ntop(AF_INET, ptr, str, sizeof(str)));
        ptr += sizeof(struct in_addr);
        len -= sizeof(struct in_addr);
    }
}
