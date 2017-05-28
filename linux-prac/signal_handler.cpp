#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>

void signal_handler(int sig)
{
    static int count = 1;
    if (sig == SIGINT) {
        std::cout << "Caught SIGINT " << count << std::endl;
        ++count;
        return ;
    }

    if (sig == SIGQUIT) {
        std::cout << "Caught SIGQUIT: exit after 5s." << std::endl;
        sleep(5);
        exit(EXIT_SUCCESS);
    }
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    for (;;)
        pause();
}
