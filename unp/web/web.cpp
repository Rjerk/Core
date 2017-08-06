#include "web.h"

void home_page(const char* host, const char* fname)
{
    int fd = Tcp_connect(host, SERV);

    char line[MAXLINE];
    int n = snprintf(line, sizeof(line), GET_CMD, fname);

    Write(fd, line, n);

    for ( ; ; ) {
        if ((n = Read(fd, line, MAXLINE)) == 0) {
            break; // server closed connection.
        }
        printf("read %d bytes of home page.\n", n);

        // do whatever with data.
        printf("data: %s\n", line);
    }

    printf("end-of-file on home page.\n");
    Close(fd);
}

void start_connect(struct file* fptr)
{
    struct addrinfo* ai = Host_serv(fptr->f_host, SERV, 0, SOCK_STREAM);

    int fd = Socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    printf("get socket: %d\n", fd);
    fptr->f_fd = fd;

    int flags = Fcntl(fd, F_GETFL, 0);
    Fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    int n;
    printf("start connect...\n");
    if ((n = connect(fd, ai->ai_addr, ai->ai_addrlen)) < 0) {
        printf("initiate nonblocking connect to the server.\n");
        if (errno != EINPROGRESS) {
            err_sys("nonblocking connect error");
        }

        fptr->f_flags = F_CONNECTING;
        FD_SET(fd, &wset);
        FD_SET(fd, &rset);
        if (fd > maxfd) {
            maxfd = fd;
        }
    } else if (n >= 0) {
        printf("write_get_cmd...\n");
        write_get_cmd(fptr);
    }
}

void write_get_cmd(struct file* fptr)
{
    char line[MAXLINE];
    int n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);

    Write(fptr->f_fd, line, n);
    printf("wrote %d bytes for %s\n", n, fptr->f_name);
}

int main(int argc, char** argv)
{
    if (argc < 5) {
        err_quit("usage: ./web <#conn> <hostname> <homepage> <file1> ...");
    }

    int maxconn = atoi(argv[1]);

    nfiles = min(argc-4, MAXFILES);
    for (int i = 0; i < nfiles; ++i) {
        file[i].f_name = argv[i+4];
        file[i].f_host = argv[2];
        file[i].f_flags = 0;
    }
    printf("nfiles = %d\n", nfiles);

    home_page(argv[2], argv[3]);

    FD_ZERO(&rset);
    FD_ZERO(&wset);
    maxfd = -1;
    nlefttoconn = nfiles;
    nlefttoread = nfiles;
    printf("%d, %d\n", nlefttoconn, nlefttoread);
    sleep(1);
    nconn = 0;
    fd_set rs, ws;
    int n;
    int flags, error;
    int fd;
    char buf[MAXLINE];
    while (nlefttoread > 0) {
        printf("nlefttoread = %d\n", nlefttoread);
        printf("nlefttoconn = %d\n", nlefttoconn);
        printf("nconn = %d, maxconn = %d\n", nconn, maxconn);
        while (nconn < maxconn && nlefttoconn > 0) {
            int i;
            for (i = 0; i < nfiles; ++i) {
                if (file[i].f_flags == 0) {
                    break;
                }
            }

            if (i == nfiles) {
                err_quit("nlefttoconn = %d but nothing found", nlefttoconn);
            }

            start_connect(&file[i]);
            sleep(3);
            ++nconn;
            --nlefttoconn;
        }

        rs = rset;
        ws = wset;
        n = Select(maxfd+1, &rs, &ws, NULL, NULL);
        for (int i = 0; i < nfiles; ++i) {
            flags = file[i].f_flags;
            if (flags == 0 || flags & F_DONE) {
                continue;
            }

            fd = file[i].f_fd;
            printf("handling file: %d\n", fd);

            if (flags & F_CONNECTING && (FD_ISSET(fd, &rs) || FD_ISSET(fd, &ws))) {
                printf("connecting...\n");
                n = sizeof(error);
                if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, (socklen_t*) &n) < 0
                        || error != 0) {
                    err_ret("nonblocking connec failed for %s", file[i].f_name);
                }

                // connection established.
                printf("connection established for %s\n", file[i].f_name);
                FD_CLR(fd, &wset); // no more writeability test.
                write_get_cmd(&file[i]);
            } else if (flags & F_READING && FD_ISSET(fd, &rs)) {
                printf("reading...\n");
                if ((n = Read(fd, buf, sizeof(buf))) == 0) {
                    printf("end-of-file on %s\n", file[i].f_name);
                    Close(fd);
                    file[i].f_flags = F_DONE;
                    FD_CLR(fd, &rset);
                    --nconn;
                    --nlefttoread;
                } else {
                    printf("read %d bytes from %s\n", n, file[n].f_name);
                }
            }
        }
    }
    exit(0);
}
