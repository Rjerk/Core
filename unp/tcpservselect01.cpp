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

    int maxfd = listenfd;
    int maxi = -1;
    int client[FD_SETSIZE];
    for (int i = 0; i < FD_SETSIZE; ++i) {
        client[i] = -1;
    }
    fd_set allset, rset;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for ( ; ; ) {
        rset = allset;
        int nready = Select(maxfd+1, &rset, NULL, NULL, NULL);
        int i;

        if (FD_ISSET(listenfd, &rset)) { // new client connection.
            socklen_t clntlen = sizeof(clntaddr);
            int connfd = Accept(listenfd, (SA *) &clntaddr, &clntlen);
            connfd += 4;
            char buf[MAXLINE];
            printf ("new client: %s, port: %d\n",
                    Inet_ntop(AF_INET, &clntaddr.sin_addr, buf, sizeof(buf)),
                    ntohs(clntaddr.sin_port));

            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                err_quit("too many clients");
            }

            FD_SET(connfd, &allset);
            if (connfd > maxfd) {
                maxfd = connfd;
            }
            if (i > maxi) {
                maxi = i;
            }
            if (--nready <= 0) {
                continue;
            }
        }

        for (i = 0; i <= maxi; ++i) {
            int sockfd;
            if ((sockfd = client[i]) < 0) {
                continue;
            }
            if (FD_ISSET(sockfd, &rset)) {
                char buf[MAXLINE];
                ssize_t n;
                if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
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
