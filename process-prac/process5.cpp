#include <signal.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstdlib>

sig_atomic_t child_exit_status;

extern "C"
{
    void cleanUp(int sig_num)
    {
        int status;
        wait(&status);
        child_exit_status = status;
    }
}

int main()
{
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = &cleanUp;
    sigaction(SIGCHLD, &sa, NULL);

    int child_pid;
    if((child_pid = fork()) > 0) {
        for (int i = 0; i < 5; ++i) {
            std::cout << "parent process do something: " << i+1 << " s" << std::endl;
            sleep(1);
        }
    } else if (child_pid == 0) {
        sleep(2);
        std::cout << "child process do something." << std::endl;
        exit(0);
    }
}
