#include <pthread.h>
#include <malloc.h>

void* allocateBuffer(size_t size)
{
    return malloc(size);
}

void deallocateBuffer(void* buffer)
{
    free(buffer);
}

void doSomething()
{
    void* temp_buffer = allocateBuffer(1024);

    // sign up clean-up function.
    pthread_cleanup_push(deallocateBuffer, temp_buffer);

    // pass non-zero to execute clean-up job.
    pthread_cleanup_pop(1);
}

int main()
{
    doSomething();
}
