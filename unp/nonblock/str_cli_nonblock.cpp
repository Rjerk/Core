#include "../unp.h"

void str_cli(FILE* fp, int sockfd)
{
    int maxfd, val, stdineof;
    ssize_t n, nwritten;
    fd_set rset, wset;
    char to[MAXLINE], fr[MAXLINE];
    char *toiptr, *tooptr, *friptr, *froptr;

    val = Fcntl(sockfd, F_GETFL, 0);
    Fcntl(sockfd, F_SETFL, val | O_NONBLOCK);
    val = Fcntl(STDIN_FILENO, F_GETFL, 0);
    Fcntl(sockfd, F_SETFL, val | O_NONBLOCK);
    val = Fcntl(STDOUT_FILENO, F_GETFL, 0);
    Fcntl(sockfd, F_SETFL, val | O_NONBLOCK);

    toiptr = tooptr = to;
    friptr = froptr = fr;
    stdineof = 0;

    maxfd = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd) + 1;

    for ( ; ; ) {
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        if (stdineof == 0 && toiptr < &to[MAXLINE]) {
            FD_SET(STDIN_FILENO, &rset);
        }
        if (friptr < &fr[MAXLINE]) {
            FD_SET(STDOUT_FILENO, &rset);
        }
        if (tooptr != toiptr) {
            FD_SET(sockfd, &wset);
        }
        if (froptr != friptr) {
            FD_SET(STDOUT_FILENO, &wset);
        }
        Select(maxfd, &rset, &wset, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &rset)) {
            if ((n = read(STDIN_FILENO, toiptr, &to[MAXLINE]-toiptr)) < 0) {
                if (errno != EWOULDBLOCK) {
                    err_sys("read error on stdin");
                }
            } else if (n == 0) {
                fprintf(stderr, "%s: EOF on stdin\n", gf_time());
                stdineof = 1; // all done with stdin.
                if (tooptr == toiptr) {
                    Shutdown(sockfd, SHUT_WR); // send FIN.
                }
            } else {
                fprintf(stderr, "%s: read %ld bytes from stdin\n", gf_time(), n);
                toiptr += n;
                FD_SET(sockfd, &wset); // try and write to sock below.
            }
        }

        if (FD_ISSET(sockfd, &rset)) {
            if (( n = read(sockfd, friptr, &fr[MAXLINE]-friptr)) < 0) {
                if (errno != EWOULDBLOCK) {
                    err_sys("read error on socket");
                }
            } else if (n == 0) {
                fprintf(stderr, "%s: EOF on socket\n", gf_time());
                if (stdineof) {
                    return ; // normal termination.
                } else {
                    err_quit("str_ci: server terminated prematurely");
                }
            } else {
                fprintf(stderr, "%s: read %ld bytes from socket\n", gf_time(), n);
                friptr += n;
                FD_SET(STDOUT_FILENO, &wset); // try and write below.
            }
        }

        if (FD_ISSET(STDOUT_FILENO, &wset) && (( n = friptr - froptr) > 0)) {
            if ((nwritten = write(STDOUT_FILENO, froptr, n)) < 0) {
                if (errno != EWOULDBLOCK) {
                    err_sys("write error to stdout");
                }
            } else {
                fprintf(stderr, "%s: wrote %ld bytes to stdout\n", gf_time(), nwritten);
                froptr += nwritten;
                if (froptr == friptr) {
                    froptr = friptr = fr; // back to beginning of buffer.
                }
            }
        }

        if (FD_ISSET(sockfd, &wset) && ((n = toiptr - tooptr) > 0)) {
            if ((nwritten = write(sockfd, tooptr, n)) < 0) {
                if (errno != EWOULDBLOCK) {
                    err_sys("write error to socket");
                }
            } else {
                fprintf(stderr, "%s: wrote %ld bytes to socket\n", gf_time(), nwritten);
                tooptr += nwritten;
                if (tooptr == toiptr) {
                    toiptr = tooptr = to; // back to beginning of buffer.
                    if (stdineof) {
                        Shutdown(sockfd, SHUT_WR); // send FIN.
                    }
                }
            }
        }
    }
}
