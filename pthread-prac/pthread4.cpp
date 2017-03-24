#include <pthread.h>

void* threadFunc(void* arg)
{
}

int main()
{
    pthread_t t;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&t, &attr, &threadFunc, NULL);
    pthread_attr_destroy(&attr);
    return 0;
}
