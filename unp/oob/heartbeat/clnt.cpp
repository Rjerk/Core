#include	"../../unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	heartbeat_cli(sockfd, 1, 5);

    fd_set rset;
	FD_ZERO(&rset);

    char sendline[MAXLINE], recvline[MAXLINE];
    int maxfdp1, stdineof = 0;
	for ( ; ; ) {
		if (stdineof == 0) {
			FD_SET(fileno(fp), &rset);
        }
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;

        if (select(maxfdp1, &rset, NULL, NULL, NULL) < 0) {
			if (errno == EINTR) {
				continue;
            } else {
				err_sys("select error");
            }
		}

		if (FD_ISSET(sockfd, &rset)) { // socket is readable.
			if (Readline(sockfd, recvline, MAXLINE) == 0) {
				if (stdineof == 1) {
					return; // normal termination.
                } else {
					err_quit("str_cli: server terminated prematurely");
                }
			}

			Writen(STDOUT_FILENO, recvline, strlen(recvline));
		}

		if (FD_ISSET(fileno(fp), &rset)) { // input is readable.
			if (Fgets(sendline, MAXLINE, fp) == NULL) {
				stdineof = 1;
				alarm(0); // turn off heartbeat.
				Shutdown(sockfd, SHUT_WR); // send FIN.
				FD_CLR(fileno(fp), &rset);
				continue;
			}

			Writen(sockfd, sendline, strlen(sendline));
		}
	}
}

int
main(int argc, char **argv)
{
	if (argc != 3) {
		err_quit("usage: ./clnt <IPaddress> <port#>");
    }

	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in	servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);

	exit(0);
}
