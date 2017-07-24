#include "../apue.h"

int main()
{
    printf ("%% ");

    char buf[MAXLINE];
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf)-1] == '\n') {
            buf[strlen(buf)-1] = '\0';
        }

        pid_t pid;
        if ((pid = fork()) < 0) {
            err_sys("fork error.");
        } else if (pid == 0) {
            execlp(buf, buf, (char*) NULL);
            err_ret("could't execute: %s", buf);
            exit(127);
        }

        int status;
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error.");
        }
        printf ("%% ");
    }
}
