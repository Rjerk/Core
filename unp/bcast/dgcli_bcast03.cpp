#include "../unp.h"

static void recvfrom_alarm(int)
{
    return ;
}

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    struct sockaddr* preply_addr = (struct sockaddr *) Malloc (servlen);

    int on = 1;
    Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    sigset_t sigset_alrm;
    Sigemptyset(&sigset_alrm);
    Sigaddset(&sigset_alrm, SIGALRM);
    Signal(SIGALRM, recvfrom_alarm);

    char sendline[MAXLINE], recvline[MAXLINE+1];
    socklen_t len;
    int n;

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        alarm(5);

        for ( ; ; ) {
            len = servlen;
            Sigprocmask(SIG_UNBLOCK, &sigset_alrm, NULL);
            n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
            Sigprocmask(SIG_BLOCK, &sigset_alrm, NULL);
            if (n < 0) {
                if (errno == EINTR) {
                    break;
                } else {
                    err_sys("recvfrom error");
                }
            } else {
                recvline[n] = 0;
                printf("from %s: %s", Sock_ntop_host(preply_addr, len), recvline);
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

