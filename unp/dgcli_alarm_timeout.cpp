#include "unp.h"

static void sig_alrm(int);

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    Signal(SIGALRM, sig_alrm);

    char sendline[MAXLINE], recvline[MAXLINE+1];
    while ((Fgets(sendline, MAXLINE, fp)) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        alarm(5);
        int n;
        if ((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
            if (errno == EINTR) {
                fprintf(stderr, "socket timeout\n");
            } else {
                err_sys("recvfrom error");
            }
        } else {
            alarm(0);
            recvline[n] = 0;
            Fputs(recvline, stdout);
        }
    }
}

static void sig_alrm(int)
{
    return ;
}
