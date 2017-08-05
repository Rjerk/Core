#include "../thread.h"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>

__thread int x = 0;

void print()
{
    std::cout << "pid = " << getpid()
              << ", tid = " << CurrentThread::tid()
              << ", name = " << CurrentThread::name()
              << ", x = " << x << std::endl;
}

int main()
{
    std::cout << "parent: " << getpid() << std::endl;
    print();
    x = 1;
    print();

    pid_t p = fork();

    if (p == 0) {
        std::cout << "child: " << getpid() << std::endl;
        print();
        x = 2;
        print();

        if (fork() == 0) {
            std::cout << "grandchild " << getpid() << std::endl;
            print();
            x = 3;
            print();
        }
    } else {
        print();
    }
}
