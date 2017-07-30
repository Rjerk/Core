#include "unpifi.h"

void free_ifi_info(struct ifi_info* ifihead)
{
    struct ifi_info* ifinext;

    for (auto ifi = ifihead; ifi != NULL; ifi = ifinext) {
        if (ifi->ifi_addr != NULL) {
            free(ifi->ifi_addr);
        }
        if (ifi->ifi_brdaddr != NULL) {
            free(ifi->ifi_brdaddr);
        }
        if (ifi->ifi_dstaddr != NULL) {
            free(ifi->ifi_dstaddr);
        }
        ifinext = ifi->ifi_next;
        free(ifi);
    }
}

struct ifi_info* Get_ifi_info(int family, int doaliases)
{
    return get_ifi_info(family, doaliases);
}

struct ifi_info* get_ifi_info(int family, int doaliases)
{
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    int lastlen = 0;
    int len = 100 * sizeof(struct ifreq); // initial buffer size guess.
    struct ifconf ifc;
    char* buf = NULL;

    for ( ; ; ) {
        buf = (char *) Malloc (len);
        ifc.ifc_len = len;
        ifc.ifc_buf = buf;

        if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
            if (errno != EINVAL || lastlen != 0) {
                err_sys("ioctl error");
            }
        } else {
            if (ifc.ifc_len == lastlen) {
                break;
            }
            lastlen = ifc.ifc_len;
        }

        len += 10 * sizeof(struct ifreq); // increment.
        free(buf);
    }

    struct ifi_info* ifihead = NULL;
    struct ifi_info* ifi = NULL;
    struct ifi_info** ifipnext = &ifihead;

    char lastname[IFNAMSIZ];
    lastname[0] = 0;
    char* sdlname = NULL;

    char* ptr = NULL;
    struct ifreq* ifr = NULL;
    struct ifreq ifrcopy;
    int myflags, flags, index = 0, hlen = 0;
    char* cptr = NULL;
    char* haddr = NULL;
    struct sockaddr_in* sinptr = NULL;
    struct sockaddr_in6* sin6ptr = NULL;
    for (ptr = buf; ptr < buf + ifc.ifc_len; ) {
        ifr = (struct ifreq *) ptr;

        switch (ifr->ifr_addr.sa_family) {
            case AF_INET6:
                len = sizeof(struct sockaddr_in6);
                break;
            case AF_INET:
            default:
                len = sizeof(struct sockaddr_in);
                break;
        }

        ptr += sizeof(ifr->ifr_name) + len;

        if (ifr->ifr_addr.sa_family != family) {
            continue; // ignore if not desired address family.
        }

        myflags = 0;
        if ((cptr = strchr(ifr->ifr_name, ':')) != NULL) {
            *cptr = 0; // replace colon with null.
        }

        if (strncmp(lastname, ifr->ifr_name, IFNAMSIZ) == 0) {
            if (doaliases == 0) {
                continue;
            }
            myflags = IFI_ALIAS;
        }
        memcpy(lastname, ifr->ifr_name, IFNAMSIZ);

        ifrcopy = *ifr;
        Ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
        flags = ifrcopy.ifr_flags;
        if ((flags & IFF_UP) == 0) {
            continue; // ignore if interface not up.
        }

        ifi = (struct ifi_info *) Calloc (1, sizeof(struct ifi_info));
        *ifipnext = ifi; // prev points to this new one.
        ifipnext = &ifi->ifi_next; // pointer to next one goes here.

        ifi->ifi_flags = flags; // IFF_xxx values.
        ifi->ifi_myflags = myflags; // IFI_xxx value.
        Ioctl(sockfd, SIOCGIFMTU, &ifrcopy);
        ifi->ifi_mtu = ifrcopy.ifr_mtu;

        memcpy(ifi->ifi_name, ifr->ifr_name, IFI_NAME);
        ifi->ifi_name[IFI_NAME-1] = '\0';

        // if the sockaddr_dl is from a different interface, ignore it.
        if (sdlname == NULL || strcmp(sdlname, ifr->ifr_name) != 0) {
            index = hlen = 0;
        }
        ifi->ifi_index = index;
        ifi->ifi_hlen = hlen;
        if (ifi->ifi_hlen > IFI_HADDR) {
            ifi->ifi_hlen = IFI_HADDR;
        }
        if (hlen) {
            memcpy(ifi->ifi_haddr, haddr, ifi->ifi_hlen);
        }

        switch (ifr->ifr_addr.sa_family) {
            case AF_INET:
                sinptr = (struct sockaddr_in *) &ifr->ifr_addr;
                ifi->ifi_addr =
                    (struct sockaddr *) Calloc (1, sizeof(struct sockaddr_in));
                memcpy(ifi->ifi_addr, sinptr, sizeof(struct sockaddr_in));

                if (flags & IFF_BROADCAST) {
                    Ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy);
                    sinptr = (struct sockaddr_in *) &ifrcopy.ifr_broadaddr;
                    ifi->ifi_brdaddr =
                        (struct sockaddr *) Calloc (1, sizeof(struct sockaddr_in));
                    memcpy(ifi->ifi_brdaddr, sinptr, sizeof(struct sockaddr_in));
                }

                if (flags & IFF_POINTOPOINT) {
                    Ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
                    sinptr = (struct sockaddr_in *) &ifrcopy.ifr_dstaddr;
                    ifi->ifi_dstaddr =
                        (struct sockaddr *) Calloc (1, sizeof(struct sockaddr_in));
                    memcpy(ifi->ifi_dstaddr, sinptr, sizeof(struct sockaddr_in));
                }
                break;
            case AF_INET6:
                sin6ptr = (struct sockaddr_in6 *) &ifr->ifr_addr;
                ifi->ifi_addr =
                    (struct sockaddr *) Calloc (1, sizeof(struct sockaddr_in));
                memcpy(ifi->ifi_addr, sin6ptr, sizeof(struct sockaddr_in));

                if (flags & IFF_POINTOPOINT) {
                    Ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
                    sin6ptr = (struct sockaddr_in6 *) &ifrcopy.ifr_dstaddr;
                    ifi->ifi_dstaddr =
                            (struct sockaddr *) Calloc (1, sizeof(struct sockaddr_in6));
                    memcpy(ifi->ifi_dstaddr, sinptr, sizeof(struct sockaddr_in6));
                }
                break;
            default:
                break;
        }
    }
    free(buf);
    return ifihead;
}
