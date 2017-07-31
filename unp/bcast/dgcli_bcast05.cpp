#include "../unp.h"
#include <setjmp.h>

static sigjmp_buf jmpbuf;

static void recvfrom_alarm(int)
{
    siglongjmp(jmpbuf, 1);
}

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    struct sockaddr* preply_addr = (struct sockaddr *) Malloc (servlen);

    int on = 1;
    Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    Signal(SIGALRM, recvfrom_alarm);

    char sendline[MAXLINE], recvline[MAXLINE+1];
    socklen_t len;
    int n;
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        alarm(1);

        for ( ; ; ) {
            if (sigsetjmp(jmpbuf, 1) != 0) {
                break;
            }

            len = servlen;
            n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
            recvline[n] = 0;
            printf("from %s: %s", Sock_ntop_host(preply_addr, len), recvline);
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

