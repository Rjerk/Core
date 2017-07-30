#include "../unp.h"
#include <netinet/udp.h>
#include <sys/sysctl.h>

int main()
{
    int mib[4];
    mib[0] = CTL_NET;
    mib[1] = AF_INET;
    mib[2] = IPPROTO_UDP;
    mib[3] = NET_NF_CONNTRACK_CHECKSUM;

    int val;
    size_t len = sizeof(val);
    Sysctl(mib, 4, &val, &len, NULL, 0);
    printf("udp checksum flag: %d\n", val);
    exit(0);
}
