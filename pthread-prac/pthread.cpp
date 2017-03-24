#include <pthread.h>
#include <iostream>

void* printA(void *unused)
{
    while (true) std::cerr << "a";
    return NULL;
}

void* printZ(void* unused)
{
    while (true) std::cerr << "z";
    return NULL;
}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &printA, NULL);
    printZ(NULL);

    return 0;
}
