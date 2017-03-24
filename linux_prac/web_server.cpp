#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cstdlib>

const int bufsize = 1024;

static const char* status_line[2] = {
    "200 OK",
    "500 Internal server error"
};

int main(int argc, char** argv)
{
    if (argc != 4) {
        printf ("Usage: %s <ip> <port> <filename>\n", basename(argv[0]));
        return -1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    const char* file_name = argv[3];

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addr_len = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*) &client, &client_addr_len);

    if (connfd < 0) {
        printf ("error is: %d\n", errno);
    } else {
        char header_buf[bufsize];
        bzero(&header_buf, sizeof(header_buf));

        char* file_buf;
        struct stat file_stat;
        bool valid = true;
        int len = 0;

        if (stat(file_name, &file_stat) < 0) { // file doesn't exist.
            valid = false;
        } else {
            if (S_ISDIR(file_stat.st_mode)) { // if file is directory.
                valid = false;
            } else if (file_stat.st_mode & S_IROTH) { // current user have read mode.
                int fd = open(file_name, O_RDONLY);
                file_buf = new char(file_stat.st_size + 1);
                bzero(&file_buf, sizeof(file_buf));
                if (read(fd, file_buf, file_stat.st_size) < 0) {
                    valid = false;
                }
            } else {
                valid = false;
            }
        }

        if (valid) {
            ret = snprintf (header_buf, bufsize-1, "%s %s\r\n", "HTTP/1.1", status_line[0]);
            len += ret;
            ret = snprintf (header_buf+len, bufsize-1-len, "Content-Length: %d\r\n", (int)file_stat.st_size);
            len += ret;
            ret = snprintf (header_buf+len, bufsize-1-len, "%s", "\r\n");

            struct iovec iv[2];
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[1].iov_base = file_buf;
            iv[1].iov_len = file_stat.st_size;
            ret = writev(connfd, iv, 2);
        } else {
            ret = snprintf (header_buf, bufsize-1, "%s %s\r\n", "HTTP1.1", status_line[1]);
            len += ret;
            ret = snprintf (header_buf+len, bufsize-1-len, "%s", "\r\n");
            send(connfd, header_buf, strlen(header_buf), 0);
        }
        close(connfd);
        delete [] file_buf;
    }

    close(sock);
    return 0;
}
