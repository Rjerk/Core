#include "unpifi.h"

void mydg_echo(int, SA*, socklen_t, SA*);

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage: ./serv <port>");
    }
    int port = atoi(argv[1]);
    int sockfd;
    const int on = 1;
    pid_t pid;
    struct sockaddr_in *sa, clntaddr, wildaddr;
    struct ifi_info *ifi = NULL, *ifihead = NULL;

    for (ifihead = ifi = Get_ifi_info(AF_INET, 1);
            ifi != NULL; ifi = ifi->ifi_next) {
        sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
        Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        sa = (struct sockaddr_in *) ifi->ifi_addr;
        sa->sin_family = AF_INET;
        sa->sin_port = htons(port);

        Bind(sockfd, (SA *) sa, sizeof(*sa));
        printf("bound %s\n", Sock_ntop((SA *) sa, sizeof(*sa)));

        if ((pid = Fork()) == 0) {
            mydg_echo(sockfd, (SA *) &clntaddr, sizeof(clntaddr), (SA *) sa);
            exit(0); // never executed.
        }

        if (ifi->ifi_flags & IFF_BROADCAST) {
            sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
            Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

            sa = (struct sockaddr_in *) ifi->ifi_brdaddr;
            sa->sin_family = AF_INET;
            sa->sin_port = htons(port);

            if (bind(sockfd, (SA *) sa, sizeof(*sa)) < 0) {
                if (errno == EADDRINUSE) {
                    printf("EADDRINUSE: %s\n", Sock_ntop((SA *) sa, sizeof(*sa)));
                    Close(sockfd);
                    continue;
                } else {
                    err_sys("bind error for %s", Sock_ntop((SA *) sa, sizeof(*sa)));
                }
            }
            printf("bound %s\n", Sock_ntop((SA *) sa, sizeof(*sa)));

            if ((pid = Fork()) == 0) {
                mydg_echo(sockfd, (SA *) &clntaddr, sizeof(clntaddr), (SA *) sa);
                exit(0);
            }
        }
    }

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&wildaddr, sizeof(wildaddr));
    wildaddr.sin_family = AF_INET;
    wildaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    wildaddr.sin_port = ntohs(port);
    Bind(sockfd, (SA *) &wildaddr, sizeof(wildaddr));
    printf("bound %s\n", Sock_ntop((SA *) &wildaddr, sizeof(wildaddr)));

    if ((pid = Fork()) == 0) {
        mydg_echo(sockfd, (SA *) &clntaddr, sizeof(clntaddr), (SA *) sa);
        exit(0); // never executed.
    }

    exit(0);
}

void mydg_echo(int sockfd, SA* pclntaddr, socklen_t clntlen, SA* myaddr)
{
    int n;
    char msg[MAXLINE];
    socklen_t len;

    for ( ; ; ) {
        len = clntlen;
        n = Recvfrom(sockfd, msg, MAXLINE, 0, pclntaddr, &len);
        printf("child %d, datagram from %s", getpid(), Sock_ntop(pclntaddr, len));
        printf(", to %s\n", Sock_ntop(myaddr, clntlen));

        Sendto(sockfd, msg, n, 0, pclntaddr, len);
    }
}
