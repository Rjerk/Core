#include <signal.h>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

sig_atomic_t sigusr1_count = 0;

extern "C"
{
    void onSigUsr1(int signal_number)
    {
        ++sigusr1_count;
    }
}

int main()
{
    std::cout << "pid: " << (int)getpid() << std::endl;
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = &onSigUsr1;
    sigaction(SIGUSR1, &sa, NULL);
    sleep(100);
    // use command "kill -s SIGUSR1 pid" in terminal, sigusr1_count plus 1
    std::cout << "SIGUSR1 counts: " << sigusr1_count << std::endl;
    return 0;
}
