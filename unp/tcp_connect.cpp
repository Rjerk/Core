#include "unp.h"

int tcp_connect(const char* host, const char* serv)
{
    struct addrinfo hints;
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int n;
    struct addrinfo* res = NULL;
    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
        err_quit("tcp_connect error for %s, %s: %s",
                 host, serv, gai_strerror(n));
    }

    struct addrinfo* ressave = res;

    int sockfd;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0) {
            continue;
        }
        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
            break;
        }
        Close(sockfd);
    } while ((res = res->ai_next) != NULL);

    freeaddrinfo(ressave);
    return sockfd;
}

int Tcp_connect(const char* host, const char* serv)
{
    return tcp_connect(host, serv);
}
