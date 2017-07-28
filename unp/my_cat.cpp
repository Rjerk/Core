#include "unp.h"

ssize_t Read_fd(int fd, void* ptr, size_t nbytes, int* recvfd)
{
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;

    struct iovec iov[1];
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;

    struct msghdr msg;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);

    ssize_t n;
    if ((n = recvmsg(fd, &msg, 0)) <= 0) {
        return n;
    }

    struct cmsghdr* cmptr;
    if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL
      && cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
        if (cmptr->cmsg_level != SOL_SOCKET) {
            err_quit("control level != SOL_SOCKET");
        }
        if (cmptr->cmsg_type != SCM_RIGHTS) {
            err_quit("control type != SCM_RIGHTS");
        }
        *recvfd = *((int *) CMSG_DATA(cmptr));
    } else {
        *recvfd = -1;
    }

    return n;
}

int my_open(const char* pathname, int mode)
{
    int sockfd[2];
    Socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);

    pid_t childpid;
    char argsockfd[10], argmode[10];
    if ((childpid = Fork()) == 0) {
        Close(sockfd[0]);
        snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
        snprintf(argmode, sizeof(argmode), "%d", mode);
        execl("./openfile", "openfile", argsockfd, pathname, argmode, (char*) NULL);
        err_sys("execl error");
    }

    Close(sockfd[1]);

    int status;
    Waitpid(childpid, &status, 0);
    if (WIFEXITED(status) == 0) {
        err_quit("child did not terminate");
    }

    char c;
    int fd;
    if ((status = WEXITSTATUS(status)) == 0) {
        Read_fd(sockfd[0], &c, 1, &fd);
    } else {
        errno = status;
        fd = -1;
    }

    Close(sockfd[0]);
    return fd;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage: ./mycat <pathname>");
    }

    int fd;
    if ((fd = my_open(argv[1], O_RDONLY)) < 0) {
        err_sys("cannot open %s", argv[1]);
    }

    int n;
    char buf[MAXLINE];
    while ((n = Read(fd, buf, MAXLINE)) > 0) {
        Write(STDOUT_FILENO, buf, n);
    }

    exit(0);
}
