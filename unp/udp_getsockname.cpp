#include "unp.h"

int main(int argc, char** argv)
{
    if (argc != 3) {
        err_quit("usage: ./udp_getsockname <ip> <port>");
    }

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr, clntaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    socklen_t len = sizeof(clntaddr);
    Getsockname(sockfd, (SA *) &clntaddr, &len);

    printf ("local address %s\n", Sock_ntop((SA *) &clntaddr, len));

    exit(0);
}
