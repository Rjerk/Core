#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

const int bufsize = 4096;

int main()
{
    int fds[2];
    pipe(fds);
    pid_t pid = fork();
    if (pid == (pid_t)0) {
        close(fds[0]); // close pipe read-end
        dup2(fds[1], STDOUT_FILENO);
        char* args[] = {"ls", "-l", "/", NULL};
        execvp(args[0], args);
    } else if (pid > 0){
        close(fds[1]);
        char buf[bufsize];
        // read datas from pipe read-end
        FILE* stream = fdopen(fds[0], "r");
        fprintf (stdout, "Data received: \n");
        while (!feof(stream) && !ferror(stream) && fgets(buf, sizeof(buf), stream) != NULL) {
            fputs(buf, stdout);
        }
        close(fds[0]);
        waitpid(pid, NULL, 0); // wait child pid exit
    }
    return 0;
}
