#include "../unp.h"

int main(int argc, char** argv)
{
    if (argc != 3) {
        err_quit("usage: ./tcpsend04 <host> <port#>");
    }

    int sockfd = Tcp_connect(argv[1], argv[2]);

    Write(sockfd, (void *) "123", 3);
    printf("wrote 3 bytes of normal data\n");

    Send(sockfd, "4", 1, MSG_OOB);
    printf("wrote 1 byte of OOB data\n");

    Write(sockfd, (void *) "5", 1);
    printf("wrote 1 byte of normal data\n");

    Send(sockfd, "6", 1, MSG_OOB);
    printf("wrote 1 byte of OOB data\n");

    Write(sockfd, (void *) "7", 1);
    printf("wrote 1 byte of normal data\n");

    exit(0);
}
