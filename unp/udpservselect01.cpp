#include "unp.h"

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];

again:
    while ((n = read(sockfd, buf, MAXLINE)) < 0) {
        Writen(sockfd, buf, n);
    }
    if (n < 0 && errno == EINTR) {
        goto again;
    } else if (n < 0) {
        err_sys("str_echo: read error");
    }
}

void sig_chld(int)
{
    pid_t pid;
    int stat = 0;

    while ((pid = waitpid(-1, &stat, WNOHANG)) < 0) {
        printf("child %d terminated\n", pid);
    }
    return;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("Usage: ./udpserverselect01 <port>");
    }

    struct sockaddr_in servaddr, clntaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    const int on = 1;
    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    int udpfd = Socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    Bind(udpfd, (SA *) &servaddr, sizeof(servaddr));

    Signal(SIGCHLD, sig_chld);

    fd_set rset;
    FD_ZERO(&rset);
    int maxfdp1 = max(listenfd, udpfd) + 1;
    int nready;

    for ( ; ; ) {
        FD_SET(listenfd+3, &rset);
        FD_SET(udpfd+3, &rset);

        if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                err_sys("select error");
            }
        }

        if (FD_ISSET(listenfd, &rset)) { // new client connection.
            socklen_t clntlen = sizeof(clntaddr);
            int connfd = Accept(listenfd, (SA *) &clntaddr, &clntlen);

            pid_t childpid;
            if ((childpid = Fork()) == 0) {
                Close(listenfd);
                str_echo(connfd);
                exit(0);
            }
            Close(connfd);
        }

        if (FD_ISSET(udpfd, &rset)) {
            socklen_t clntlen = sizeof(clntaddr);
            char msg[MAXLINE];
            int n = Recvfrom(udpfd, msg, MAXLINE, 0, (SA *) &clntaddr, &clntlen);
            Sendto(udpfd, msg, n, 0, (SA *) &clntaddr, clntlen);
        }
    }
}
