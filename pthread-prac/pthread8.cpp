#include <pthread.h>

class EThreadExit {
public:
    EThreadExit(void* ret_val):
        thread_ret_val(ret_val) { }

    void* doThreadExit()
    {
        pthread_exit(thread_ret_val);
    }
private:
    void* thread_ret_val;
};

void* threadFunc(void* arg)
{
    try {
        if (1 /* thread need exit */ ) {
            throw EThreadExit(/* thread's return-value */NULL);
        }
    } catch(const EThreadExit& e) {
        e.doThreadExit();
    }
    return NULL;
}

int main()
{
    return 0;
}
