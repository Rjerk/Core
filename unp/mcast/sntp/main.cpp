#include "sntp.h"
#include "../../ioctl/unpifi.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage: ./ssntp <IPaddress>");
    }

    struct sockaddr *mcastsa = NULL;
    socklen_t salen;

    int sockfd;
    sockfd = Udp_client(argv[1], "ntp", (SA **) &mcastsa, &salen);
    printf("sockfd: %d\n", sockfd);
    printf("salen: %d\n", salen);
    auto wild = (SA *) Malloc (salen);
    memcpy(wild, mcastsa, salen);
    sock_set_wild(wild, salen);
    Bind(sockfd, wild, salen);

    struct ifi_info* ifi = NULL;
    for (ifi = Get_ifi_info(mcastsa->sa_family, 1);
                ifi != NULL; ifi = ifi->ifi_next) {
        if (ifi->ifi_flags & IFF_MULTICAST) {
            Mcast_join(sockfd, mcastsa, salen, ifi->ifi_name, 0);
            printf("joined %s on %s\n",
                    Sock_ntop(mcastsa, salen), ifi->ifi_name);
        }
    }

    socklen_t len;
    ssize_t n;
    char buf[MAXLINE];
    struct timeval now;
    auto from = (SA *) Malloc (salen);
    for ( ; ; ) {
        len = salen;
        n = Recvfrom(sockfd, buf, sizeof(buf), 0, from, &len);
        Gettimeofday(&now, NULL);
        sntp_proc(buf, n, &now);
    }
}
