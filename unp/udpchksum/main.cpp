#include "udpchksum.h"
#include <setjmp.h>
#include <netinet/udp.h>

struct sockaddr *dest = nullptr, *local = nullptr;
struct sockaddr_in locallookup;
socklen_t destlen, locallen;

int dataklink; // from pcap_datalink(), in <net/bpf.h>
char* device; // pcap device.
pcap_t* pd; // packet capture struct pointer.
int rawfd; // raw socket to write on.
int snaplen = 200; // amount of data to capture.
int verbose;
int zerosum; // send UDP query with no checksum.

#define CMD "udp and src host %s and src port %d"

static void usage(const char*)
{
    err_msg(
        "usage: udpcksum [ options ] <host> <serv>\n"
        "options: -0    send UDP datagram with checksum set to 0\n"
        "         -i s  packet capture device\n"
        "         -l a.b.c.d.p  local IP=a.b.c.d, local port=p\n"
        "         -v    verbose output"
    );
    exit(1);
}

static sigjmp_buf jmpbuf;
static int canjump;

void sig_alrm(int)
{
    if (canjump == 0) {
        return ;
    }
    siglongjmp(jmpbuf, 1);
}

void open_output()
{
    int on = 1;

    rawfd = Socket(dest->sa_family, SOCK_RAW, 0);

    Setsockopt(rawfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));
}

void open_pcap()
{
    uint32_t localnet, netmask = 0;
    char cmd[MAXLINE], errbuf[PCAP_ERRBUF_SIZE],
            str1[INET_ADDRSTRLEN], str2[INET_ADDRSTRLEN];
    struct bpf_program fcode;

    // if not use -i specify the device, then choose one by pcap_lookupdev.
    if (device == NULL) {
        if ((device = pcap_lookupdev(errbuf)) == NULL) {
            err_quit("pcap_lookupdev: %s", errbuf);
        }
    }
    printf("device = %s\n", device);

    // open the device.
    if ((pd = pcap_open_live(device, snaplen, 0, 500, errbuf)) == NULL) {
        err_quit("pcap_open_live: %s", errbuf);
    }

    if (verbose) {
        printf("localnet = %s, netmask = %s\n",
                    Inet_ntop(AF_INET, &localnet, str1, sizeof(str1)),
                    Inet_ntop(AF_INET, &localnet, str2, sizeof(str2)));
    }

    snprintf(cmd, sizeof(cmd), CMD, Sock_ntop_host(dest, destlen),
                        ntohs(sock_get_port(dest, destlen)));

    if (verbose) {
        printf("cmd = %s\n", cmd);
    }

    // compile cmd to filter program.
    if (pcap_compile(pd, &fcode, cmd, 0, netmask) < 0) {
        err_quit("pcap_compile: %s", pcap_geterr(pd));
    }

    // load filter to device.
    if (pcap_setfilter(pd, &fcode) < 0) {
        err_quit("pcap_setfilter: %s", pcap_geterr(pd));
    }

    // get datalink type.
    if ((datalink = pcap_datalink(pd)) < 0) {
        err_quit("pcap_datalink: %s", pcap_geterr(pd));
    }

    if (verbose) {
        printf("datalink = %d\n", datalink);
    }
}

void test_udp()
{
    volatile int nsent = 0, timeout = 3;
    struct udphdr* ui = nullptr;
    Signal(SIGALRM, sig_alrm);

    if (sigsetjmp(jmpbuf, 1)) {
        if (nsent >= 3) {
            err_quit("no response");
        }
        printf("timeout\n");
        timeout *= 2;
    }
    canjump = 1;

    send_dns_query();
    ++nsent;

    alarm(timeout);
    ui = udp_read();
    canjump = 0;
    alarm(0);

    if (ui->check == 0) {
        printf("UDP checksums off\n");
    }
}

char* next_pcap(int* len)
{
    char* ptr;
    struct pcap_pkthdr hdr;

    while ((ptr = (char *) pcap_next(pd, &hdr)) == NULL) ;

    *len = hdr.caplen; // captured length.

    return ptr;
}

struct udphdr* udp_check(char* ptr, int len)
{
    long hlen = 0;
    struct ip* ip;
    struct udphdr* ui;

    if (len < (int)(sizeof(struct ip) + sizeof(struct udphdr))) {
        err_quit("len = %d", len);
    }

    ip = (struct ip *) ptr;
    if (ip->ip_v != IPVERSION) {
        err_quit("ip_v = %d", ip->ip_v);
    }

    len = ip->ip_hl << 2;
    if (hlen < (int)(sizeof(struct ip))) {
        err_quit("ip_hl = %d", ip->ip_hl);
    }

    if ((ip->ip_sum = in_cksum((uint16_t *) ip, hlen)) != 0) {
        err_quit("ip checksum error");
    }

    if (ip->ip_p == IPPROTO_UDP) {
        ui = (struct udphdr *) ip;
        return ui;
    } else {
        err_quit("not a UDP packet");
    }
    return NULL;
}

void udp_write(char* buf, int userlen)
{
    struct udphdr* ui;
    struct ip* ip;

    ip = (struct ip *) buf;
    ui = (struct udphdr *) buf;
    bzero(ui, sizeof(*ui));

    ui->uh_ulen = htons((uint16_t) (sizeof(struct udphdr) + userlen));
    userlen += sizeof(struct udphdr);

    ui->ui_pr = IPPROTO_UDP;
    ui->ui_src.s_addr = ((struct sockaddr_in *) local)->sin_addr.s_addr;
    ui->ui_dst.s_addr = ((struct sockaddr_in *) dest)->sin_addr.s_addr;
    ui->ui_sport = ((struct sockaddr_in *) local)->sin_port;
    ui->ui_dport = ((struct sockaddr_in *) dest)->sin_port;
    ui->ui_ulen = ui->ui_len;

    if (zerosum == 0) {
#if 1
    if ( (ui->ui_sum = in_cksum((u_int16_t *) ui, userlen)) == 0)
        ui->ui_sum = 0xffff;
#else
    ui->ui_sum = ui->ui_len;
#endif
    }

    ip->ip_v = IPVERSION;
    ip->ip_hl = sizeof(struct ip) >> 2;
    ip->ip_tos = 0;
#if defined(linux) || defined(__OpenBSD__)
    ip->ip_len = htons(userlen);
#else
    ip->ip_len = userlen;
#endif
    ip->ip_id = 0;
    ip->ip_off = 0;
    ip->ip_ttl = TTL_OUT;

    Sendto(rawfd, buf, userlen, 0, dest, destlen);

}

struct udphdr* udp_read(void)
{
    int len;
    char* ptr;
    struct ether_header* eptr;

    for ( ; ; ) {
        ptr = next_pcap(&len);

        switch(datalink) {
            case DLT_NULL:
                return (udp_check(ptr+4, len-4));

            case DTL_EN10MB:
                eptr = (struct ether_header *) ptr;
                if (ntohs(eptr->type) != ETHERTYPE_IP) {
                    err_quit("Ethernet type %x not IP", ntohs(eptr->ether_type));
                }
                return udp_check(ptr+14, len-14);

            case DTL_SLIP:
                return udp_check(ptr+24, len-24);

            case DTL_PPP:
                return udp_check(ptr+24, len-24);

            default:
                err_quit("unsupported datalink (%d)", datalink);
        }
    }
}

void cleanup(int )
{
    struct pcap_stat stat;
    putc('\n', stdout);

    if (verbose) {
        if (pcap_stats(pd, &stat) < 0) {
            err_quit("pcap_stats: %s\n", pcap_geterr(pd));
        }
        printf("%d packets received by filter\n", stat.ps_recv);
        printf("%d packets dropped by kernel\n", stat.ps_drop);
    }
}

void send_dns_query(void)
{
    size_t nbytes;
    // use -D_BSD_SOURCE macro as parameter of g++ !
    char* buf = (char *) Malloc (sizeof(struct udphdr) + 100);
    char* ptr = buf + sizeof(struct udphdr); // leav room for IP/UDP headers.

    *((uint16_t *) ptr) = htons(1024); // identification.
    ptr += 2;

    *((uint16_t *) ptr) = htons(0x0100); // flags: recursion desired.
    ptr += 2;

    *((uint16_t *) ptr) = htons(1); // # questions.
    ptr += 2;

    *((uint16_t *) ptr) = 0; // # answer RRs.
    ptr += 2;

    *((uint16_t *) ptr) = 0; // # authority RRs.
    ptr += 2;

    *((uint16_t *) ptr) = 0; // # additional RRs.
    ptr += 2;

    memcpy(ptr, "\001a\014root-servers\003net\000", 20);
    ptr += 20;
    *((uint16_t *) ptr) = htons(1); // query type = A.
    ptr += 2;
    *((uint16_t *) ptr) = htons(1); // query class = 1 (IP addr).
    ptr += 2;

    nbytes = (ptr - buf);
    udp_write(buf, nbytes);

    if (verbose) {
        printf("sent: %ld bytes of data\n", nbytes);
    }
}


int main(int argc, char** argv)
{
    int c, lopt = 0;
    char *ptr, localname[1024], *localport;
    struct addrinfo* aip;
    opterr = 0;
    while (( c = getopt(argc, argv, "Oi:l:v")) != -1) {
        switch (c) {
            case 'O':
                zerosum = 1;
                break;
            case 'i':
                device = optarg; // pcap device.
                break;
            case 'l': // local IP address and port #: a.b.c.d.port
                if ((ptr = strrchr(optarg, ',')) == NULL) {
                    usage("invalid -l option");
                }

                *ptr++ = 0; // null replaces final period.
                localport = ptr;
                strncpy(localname, optarg, sizeof(localname));
                lopt = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case '?':
                usage("unrecognized option");
        }
    }

    if (optind != argc-2) {
        usage("missing <host> and/or <serv>");
    }

    aip = Host_serv(argv[optind], argv[optind+1], AF_INET, SOCK_DGRAM);
    dest = aip->ai_addr; // don't freeaddrinfo().
    destlen = aip->ai_addrlen;

    if (lopt) {
        aip = Host_serv(localname, localport, AF_INET, SOCK_DGRAM);
        local = aip->ai_addr;
        locallen = aip->ai_addrlen;
    } else {
        int s = Socket(AF_INET, SOCK_DGRAM, 0);
        Connect(s, dest, destlen);
        locallen = sizeof(locallookup);
        local = (struct sockaddr *) &locallookup;
        Getsockname(s, local, &locallen);
        if (locallookup.sin_addr.s_addr == htonl(INADDR_ANY)) {
            err_quit("Can't determine local address - use -l\n");
        }
        close(s);
    }

    open_output(); // open output, either raw socket or libnet.

    open_pcap(); // open packet capture device.

    setuid(getuid()); // don't need superuser privileges anymore.

    Signal(SIGTERM, cleanup);
    Signal(SIGINT, cleanup);
    Signal(SIGHUP, cleanup);

    test_udp();

    cleanup(0);
}
