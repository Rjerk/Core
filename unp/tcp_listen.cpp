#include "unp.h"

int tcp_listen(const char* host, const char* serv, socklen_t* addrlenp)
{
    struct addrinfo hints;
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int n;
    struct addrinfo* res = NULL;
    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
        err_quit("tcp_listen error for %s, %s: %s",
                 host, serv, gai_strerror(n));
    }
    struct addrinfo* ressave = res;

    int listenfd;
    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0) {
            continue;
        }

        int on = 1;
        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(n));
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0) {
            break;
        }

        Close(listenfd);
    } while ((res = res->ai_next) != NULL);

    if (res == NULL) {
        err_sys("tcp_listen error for %s, %s", host, serv);
    }

    Listen(listenfd, LISTENQ);

    if (addrlenp) {
        *addrlenp = res->ai_addrlen;
    }
    freeaddrinfo(ressave);
    return listenfd;
}

int Tcp_listen(const char* host, const char* server, socklen_t* addrlenp)
{
    return tcp_listen(host, server, addrlenp);
}
