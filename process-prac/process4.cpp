#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int spawn(char* program, char** args)
{
    pid_t child_pid = fork();
    if (child_pid > 0) {
        return child_pid;
    } else if (child_pid == 0) {
        execvp(program, args);
        // only errors occur, the execvp return value.
        std::cerr << "Error occurred when executing execvp." << std::endl;
        abort();
    }
}

int main()
{
    char* args[] = {"ls", "-l", "/", NULL};
    spawn("ls", args);

    int child_status;
    wait(&child_status);
    if (WIFEXITED(child_status)) {
        std::cout << "Exited normally with: " << WEXITSTATUS(child_status) << std::endl;
    } else {
        std::cout << "Exited abnormally." << std::endl;
    }

    std::cout << "Done!" << std::endl;
}
