#include <sys/socket.h>
#include <sys/types.h>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    const char* str = "This is a string\n";
    int ret = -1;
    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret == 0);
    char buf[100];
    pid_t pid;
    int status;

    if ((pid = fork()) > 0) {
        printf ("parent's pid: %d\n", getpid());
        // close(pipefd[0]);
        close(pipefd[1]);
        if ((ret = write(pipefd[0], str, strlen(str))) < 0) {
            exit(-1);
        }
        wait(&status);
    } else if (pid == 0) {
        printf ("child's pid: %d\n", getpid());
        // close(pipefd[1]);
        close(pipefd[0]);
        if ((ret = read(pipefd[1], buf, strlen(str))) < 0) {
            exit(-2);
        }
        buf[strlen(str)] = '\0';
        printf ("child receive: %s\n", buf);
        exit(0);
    } else {
        exit(-3);
    }
    return 0;
}
