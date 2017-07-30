#ifndef UNP_IFI_H
#define UNP_IFI_H

#include "../unp.h"
#include <net/if.h>

#define IFI_NAME 16
#define IFI_HADDR 8

struct ifi_info {
    char ifi_name[IFI_NAME]; // iterface name, null-terminated.
    short ifi_index; // iterface index.
    short ifi_mtu; // iterface mtu.
    u_char ifi_haddr[IFI_HADDR]; // hardware address.
    u_short ifi_hlen; // # bytes in hardware address: 0, 6, 8
    short ifi_flags; // IFF_xxx constants from <net/if.h>
    short ifi_myflags; // our own IFI_xxx flags.
    struct sockaddr* ifi_addr; // primary address.
    struct sockaddr* ifi_brdaddr; // broadcast address.
    struct sockaddr* ifi_dstaddr; // destination address.
    struct ifi_info* ifi_next; // next of these structures.
};

#define IFI_ALIAS 1 // ifi_addr is an alias.

struct ifi_info* get_ifi_info(int, int);
struct ifi_info* Get_ifi_info(int, int);
void free_ifi_info(struct ifi_info*);


#endif
