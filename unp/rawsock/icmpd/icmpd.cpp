#include "icmpd.h"
#include	<netinet/in_systm.h>
#include	<netinet/ip.h>
#include	<netinet/ip_icmp.h>
#include	<netinet/udp.h>

#ifdef	IPV6
#include	<netinet/ip6.h>
#include	<netinet/icmp6.h>
#endif

int readable_v4(void)
{
	int					i, hlen1, hlen2, icmplen, sport;
	char				buf[MAXLINE];
	char				srcstr[INET_ADDRSTRLEN], dststr[INET_ADDRSTRLEN];
	ssize_t				n;
	socklen_t			len;
	struct ip			*ip, *hip;
	struct icmp			*icmp;
	struct udphdr		*udp;
	struct sockaddr_in	from, dest;
	struct icmpd_err	icmpd_err;

	len = sizeof(from);
	n = Recvfrom(fd4, buf, MAXLINE, 0, (SA *) &from, &len);

	printf("%ld bytes ICMPv4 from %s:", n, Sock_ntop_host((SA *) &from, len));

	ip = (struct ip *) buf;		/* start of IP header */
	hlen1 = ip->ip_hl << 2;		/* length of IP header */

	icmp = (struct icmp *) (buf + hlen1);	/* start of ICMP header */
	if ( (icmplen = n - hlen1) < 8)
		err_quit("icmplen (%d) < 8", icmplen);

	printf(" type = %d, code = %d\n", icmp->icmp_type, icmp->icmp_code);
/* end readable_v41 */

/* include readable_v42 */
	if (icmp->icmp_type == ICMP_UNREACH ||
		icmp->icmp_type == ICMP_TIMXCEED ||
		icmp->icmp_type == ICMP_SOURCEQUENCH) {
		if (icmplen < 8 + 20 + 8)
			err_quit("icmplen (%d) < 8 + 20 + 8", icmplen);

		hip = (struct ip *) (buf + hlen1 + 8);
		hlen2 = hip->ip_hl << 2;
		printf("\tsrcip = %s, dstip = %s, proto = %d\n",
			   Inet_ntop(AF_INET, &hip->ip_src, srcstr, (socklen_t) sizeof(srcstr)),
			   Inet_ntop(AF_INET, &hip->ip_dst, dststr, (socklen_t) sizeof(dststr)),
			   hip->ip_p);
 		if (hip->ip_p == IPPROTO_UDP) {
			udp = (struct udphdr *) (buf + hlen1 + 8 + hlen2);
			sport = udp->uh_sport;

				/* 4find client's Unix domain socket, send headers */
			for (i = 0; i <= maxi; i++) {
				if (client[i].connfd >= 0 &&
					client[i].family == AF_INET &&
					client[i].lport == sport) {

					bzero(&dest, sizeof(dest));
					dest.sin_family = AF_INET;
#ifdef	HAVE_SOCKADDR_SA_LEN
					dest.sin_len = sizeof(dest);
#endif
					memcpy(&dest.sin_addr, &hip->ip_dst,
						   sizeof(struct in_addr));
					dest.sin_port = udp->uh_dport;

					icmpd_err.icmpd_type = icmp->icmp_type;
					icmpd_err.icmpd_code = icmp->icmp_code;
					icmpd_err.icmpd_len = sizeof(struct sockaddr_in);
					memcpy(&icmpd_err.icmpd_dest, &dest, sizeof(dest));

						/* 4convert type & code to reasonable errno value */
					icmpd_err.icmpd_errno = EHOSTUNREACH;	/* default */
					if (icmp->icmp_type == ICMP_UNREACH) {
						if (icmp->icmp_code == ICMP_UNREACH_PORT)
							icmpd_err.icmpd_errno = ECONNREFUSED;
						else if (icmp->icmp_code == ICMP_UNREACH_NEEDFRAG)
							icmpd_err.icmpd_errno = EMSGSIZE;
					}
					Write(client[i].connfd, &icmpd_err, sizeof(icmpd_err));
				}
			}
		}
	}
	return(--nready);
}

int readable_v6(void)
{
#ifdef	IPV6
	int					i, hlen2, icmp6len, sport;
	char				buf[MAXLINE];
	char				srcstr[INET6_ADDRSTRLEN], dststr[INET6_ADDRSTRLEN];
	ssize_t				n;
	socklen_t			len;
	struct ip6_hdr		*hip6;
	struct icmp6_hdr	*icmp6;
	struct udphdr		*udp;
	struct sockaddr_in6	from, dest;
	struct icmpd_err	icmpd_err;

	len = sizeof(from);
	n = Recvfrom(fd6, buf, MAXLINE, 0, (SA *) &from, &len);

	printf("%ld bytes ICMPv6 from %s:",
		   n, Sock_ntop_host((SA *) &from, len));

	icmp6 = (struct icmp6_hdr *) buf;		/* start of ICMPv6 header */
	if ( (icmp6len = n) < 8)
		err_quit("icmp6len (%d) < 8", icmp6len);

	printf(" type = %d, code = %d\n", icmp6->icmp6_type, icmp6->icmp6_code);
/* end readable_v61 */

/* include readable_v62 */
	if (icmp6->icmp6_type == ICMP6_DST_UNREACH ||
		icmp6->icmp6_type == ICMP6_PACKET_TOO_BIG ||
		icmp6->icmp6_type == ICMP6_TIME_EXCEEDED) {
		if (icmp6len < 8 + 8)
			err_quit("icmp6len (%d) < 8 + 8", icmp6len);

		hip6 = (struct ip6_hdr *) (buf + 8);
		hlen2 = sizeof(struct ip6_hdr);
		printf("\tsrcip = %s, dstip = %s, next hdr = %d\n",
			   Inet_ntop(AF_INET6, &hip6->ip6_src, srcstr, sizeof(srcstr)),
			   Inet_ntop(AF_INET6, &hip6->ip6_dst, dststr, sizeof(dststr)),
			   hip6->ip6_nxt);
 		if (hip6->ip6_nxt == IPPROTO_UDP) {
			udp = (struct udphdr *) (buf + 8 + hlen2);
			sport = udp->uh_sport;

				/* 4find client's Unix domain socket, send headers */
			for (i = 0; i <= maxi; i++) {
				if (client[i].connfd >= 0 &&
					client[i].family == AF_INET6 &&
					client[i].lport == sport) {

					bzero(&dest, sizeof(dest));
					dest.sin6_family = AF_INET6;
#ifdef	HAVE_SOCKADDR_SA_LEN
					dest.sin6_len = sizeof(dest);
#endif
					memcpy(&dest.sin6_addr, &hip6->ip6_dst,
						   sizeof(struct in6_addr));
					dest.sin6_port = udp->uh_dport;

					icmpd_err.icmpd_type = icmp6->icmp6_type;
					icmpd_err.icmpd_code = icmp6->icmp6_code;
					icmpd_err.icmpd_len = sizeof(struct sockaddr_in6);
					memcpy(&icmpd_err.icmpd_dest, &dest, sizeof(dest));

						/* 4convert type & code to reasonable errno value */
					icmpd_err.icmpd_errno = EHOSTUNREACH;	/* default */
					if (icmp6->icmp6_type == ICMP6_DST_UNREACH &&
						icmp6->icmp6_code == ICMP6_DST_UNREACH_NOPORT)
						icmpd_err.icmpd_errno = ECONNREFUSED;
					if (icmp6->icmp6_type == ICMP6_PACKET_TOO_BIG)
							icmpd_err.icmpd_errno = EMSGSIZE;
					Write(client[i].connfd, &icmpd_err, sizeof(icmpd_err));
				}
			}
		}
	}
	return(--nready);
#endif
}

int readable_listen(void)
{
    int i, connfd;
    socklen_t clntlen = sizeof(clntaddr);
    connfd = Accept(listenfd, (SA *) &clntaddr, &clntlen);

    for (i = 0; i < FD_SETSIZE; ++i) {
        if (client[i].connfd < 0) {
            client[i].connfd = connfd; // save descriptors.
            break;
        }
    }

    if (i == FD_SETSIZE) {
        close(connfd);
        return --nready;
    }

    printf("new connection, i = %d, connfd = %d\n", i, connfd);

    FD_SET(connfd, &allset);

    if (connfd > maxfd) {
        maxfd = connfd; // for select.
    }
    if (i > maxi) {
        maxi = i;
    }

    return --nready;
}

int readable_conn(int i)
{
    int unixfd, recvfd;
    char c;
    ssize_t n;
    socklen_t len;
    struct sockaddr_storage ss;

    unixfd = client[i].connfd;
    recvfd = -1;
    if ((n = Read_fd(unixfd, &c, 1, &recvfd)) == 0) {
        err_msg("client %d terminated, recvfd = %d", i, recvfd);
        goto clientdone;
    }

    if (recvfd < 0) {
        err_msg("read_fd did not return descriptors");
        goto clienterr;
    }

    len = sizeof(ss);
    if (getsockname(recvfd, (SA *) &ss, &len) < 0) {
        err_ret("getsockname error");
        goto clienterr;
    }

    client[i].family = ss.ss_family;
    if ((client[i].lport = sock_get_port((SA *) &ss, len)) == 0) {
        client[i].lport = sock_bind_wild(recvfd, client[i].family);
        if (client[i].lport <= 0) {
            err_ret("error binding ephemeral port");
            goto clienterr;
        }
    }

    Write(unixfd, (void *) "1", 1); // tell client all OK.
    Close(recvfd); // all done with client's UDP socket.
    return --nready;

clienterr:
    Write(unixfd, (void *) "0", 1); // tell client error occurred.
clientdone:
    Close(unixfd);
    if (recvfd >= 0) {
        Close(recvfd);
    }
    FD_CLR(unixfd, &allset);
    client[i].connfd = -1;
    return --nready;
}


int main(int argc, char**)
{
    int i, sockfd;
    struct sockaddr_un sun;

    if (argc != 1) {
        err_quit("usage: ./icmpd");
    }

    maxi = -1;
    for (i = 0; i < FD_SETSIZE; ++i) {
        client[i].connfd = -1; // -1 indicates available entry.
    }
    FD_ZERO(&allset);

    fd4 = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    FD_SET(fd4, &allset);
    maxfd = fd4;

#ifdef IPV6
    fd6 = Socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
    FD_SET(fd6, &allset);
    maxfd = max(maxfd, fd6);
#endif

    listenfd = Socket(AF_UNIX, SOCK_STREAM, 0);
    sun.sun_family = AF_LOCAL;
    strncpy(sun.sun_path, ICMPD_PATH, strlen(ICMPD_PATH));
    unlink(ICMPD_PATH);
    Bind(listenfd, (SA *) &sun, sizeof(sun));
    Listen(listenfd, LISTENQ);
    FD_SET(listenfd, &allset);
    maxfd = max(maxfd, listenfd);

    for ( ; ; ) {
        rset = allset;
        nready = Select(maxfd+1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &rset)) {
            if (readable_listen() <= 0) {
                continue;
            }
        }

        if (FD_ISSET(fd4, &rset)) {
            if (readable_v4() <= 0) {
                continue;
            }
        }

#ifdef IPV6
        if (FD_ISSET(fd6, &rset)) {
            if (readable_v6() <= 0) {
                continue;
            }
        }
#endif
        for (i = 0; i <= maxi; ++i) {
            if ((sockfd = client[i].connfd)) {
                continue;
            }

            if (FD_ISSET(sockfd, &rset)) {
                if (readable_conn(i) <= 0) {
                    break; // no more readable descriptors.
                }
            }
        }
    }
    exit(0);
}
