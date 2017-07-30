#include "unproute.h"

#define BUFLEN (sizeof(struct rt_msghdr) + 512)

#define SEQ 9999

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage: ./getrt <IPaddress>");
    }

    int sockfd = Socket(AF_ROUTE, SOCK_RAW, 0);

    char* buf = (char *) Calloc (1, BUFLEN);

    struct rt_msghdr* rtm = (struct rt_msghdr *) buf;
    rtm->rtm_msglen = sizeof(struct rt_msghdr) + sizeof(struct sockaddr_in);
    rtm->
}
