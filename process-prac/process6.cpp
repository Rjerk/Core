#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid > 0) {
        exit(EXIT_SUCCESS);
    } else if (pid == 0) {
        // child process's new session
        if (setsid() == -1) {
            return -2;
        }
        // set working directory.
        if (chdir("/") == -1) {
            return -3;
        }
        // reset file mask.
        umask(0);
        // close file descriptor.
        for (int i = 0; i < 3; ++i) {
            close(i);
        }
        // redirect standard stream to dump device
        open("/dev/null", O_RDWR); // stdin
        dup(0); // stdout 0 -> 1
        dup(0); // stderr 0 -> 2
        // deamon is wroking.
    }
    return 0;
}
