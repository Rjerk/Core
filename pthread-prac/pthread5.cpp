#include <pthread.h>

int main()
{
    int ocs;
    double account[2] = {100, 100};
    int to = 0;
    int from = 1;
    double amount = 100;

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &ocs);

    account[to] += amount;
    account[from] -= amount;

    pthread_setcancelstate(ocs, NULL);
}
