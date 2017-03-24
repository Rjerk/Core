#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

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
    std::cout << "Done!" << std::endl;
}
