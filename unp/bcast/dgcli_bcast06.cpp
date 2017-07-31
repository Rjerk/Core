#include "../unp.h"

static int pipefd[2];

static void recvfrom_alarm(int)
{
    Write(pipefd[1], (void*) "", 1);
    return ;
}

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    struct sockaddr* preply_addr = (struct sockaddr *) Malloc (servlen);

    int on = 1;
    Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    Pipe(pipefd);
    int maxfdp1 = max(sockfd, pipefd[0]) + 1;

    fd_set rset;
    FD_ZERO(&rset);

    Signal(SIGALRM, recvfrom_alarm);

    char sendline[MAXLINE], recvline[MAXLINE+1];
    socklen_t len;
    int n;
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        alarm(5);

        for ( ; ; ) {
            FD_SET(sockfd, &rset);
            FD_SET(pipefd[0], &rset);

            if ((n = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
                if (errno == EINTR) {
                    continue;
                } else {
                    err_sys("select error");
                }
            }

            if (FD_ISSET(sockfd, &rset)) {
                len = servlen;
                n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
                recvline[n] = 0;
                printf("from %s: %s", Sock_ntop(preply_addr, len), recvline);
            }

            if (FD_ISSET(pipefd[0], &rset)) {
                Read(pipefd[0], &n, 1);
                break;
            }
        }
    }
    free(preply_addr);
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        err_quit("usage: ./dgcli_bcast <ip> <port>");
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

    exit(0);
}

