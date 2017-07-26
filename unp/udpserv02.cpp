#include "unp.h"

static int count = 0;

static void recvfrom_int(int)
{
    printf ("\nrecieved %d datagrams\n", count);
    exit(0);
}

void dg_echo(int sockfd, SA* pclntaddr, socklen_t clnt_len)
{
    char msg[MAXLINE];
    socklen_t len;

    Signal(SIGINT, recvfrom_int);

    for ( ; ; ) {
        len = clnt_len;
        Recvfrom(sockfd, msg, MAXLINE, 0, pclntaddr, &len);
        ++count;
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage: ./udpserv01 <port>");
    }
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr, clntaddr;
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SA *) &clntaddr, sizeof(clntaddr));
}
