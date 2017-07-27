#include "unp.h"

int udp_client(const char* host, const char* serv, socklen_t* addrlenp)
{
    struct addrinfo hints;
    bzero(&hints, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    int n;
    struct addrinfo* res = NULL;
    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
        err_quit("udp_client error for %s, %s: %s",
                 host, serv, gai_strerror(n));
    }
    struct addrinfo* ressave = res;

    int sockfd;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0) {
            continue;
        }

        if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
            break;
        }

        Close(sockfd);
    } while ((res = res->ai_next) != NULL);

    if (res == NULL) {
        err_sys("udp_server error for %s, %s", host, serv);
    }

    if (addrlenp) {
        *addrlenp = res->ai_addrlen;
    }

    freeaddrinfo(ressave);

    return sockfd;
}

