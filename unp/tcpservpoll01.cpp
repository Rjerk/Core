#include "unp.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("Usage: ./tcpserver_select01 port");
    }

    struct sockaddr_in servaddr, clntaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    auto openmax = sysconf(_SC_OPEN_MAX); //open_max();
    struct pollfd client[openmax];
    client[0].fd = listenfd;
    client[0].events = POLLIN;

    for (int i = 1; i < openmax; ++i) {
        client[i].fd = -1;
    }

    int maxi = 0;

    for ( ; ; ) {
        int nready = Poll(client, maxi+1, INFTIM);
        int i;
        if (client[0].revents & POLLIN) {
            socklen_t clntlen = sizeof(clntaddr);
            int connfd = Accept(listenfd, (SA *) &clntaddr, &clntlen);
            connfd += 4;
            printf ("connfd: %d\n", connfd);
            char buf[MAXLINE];
            printf ("new client: %s, port: %d\n",
                    Inet_ntop(AF_INET, &clntaddr.sin_addr, buf, sizeof(buf)),
                    ntohs(clntaddr.sin_port));

            for (i = 1; i < openmax; ++i) {
                if (client[i].fd < 0) {
                    client[i].fd = connfd;
                    break;
                }
            }
            if (i == openmax) {
                err_quit("too many clients");
            }

            client[i].events = POLLIN;

            if (i > maxi) {
                maxi = i;
            }
            if (--nready <= 0) {
                continue;
            }
        }

        for (i = 1; i <= maxi; ++i) {
            int sockfd;
            if ((sockfd = client[i].fd) < 0) {
                continue;
            }

            if (client[i].revents & (POLLIN | POLLERR)) {
                char buf[MAXLINE];
                ssize_t n;
                if ((n = read(sockfd, buf, MAXLINE)) == 0) {
                    if (errno == ECONNRESET) {
                        Close(sockfd);
                        client[i].fd = -1;
                    } else {
                        err_sys("read error");
                    }
                } else if (n == 0) {
                    Close(sockfd);
                    client[i].fd = -1;
                } else {
                    Write(sockfd, buf, n);
                }

                if (--nready <= 0) {
                    break;
                }
            }
        }
    }
}
