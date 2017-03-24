#include <iostream>
#include <pthread.h>
#include <cmath>

// compile: g++ pthread3.cpp -o -lpthread -lm -fpermissive

void* isPrime(void* n)
{
    unsigned int p = reinterpret_cast<unsigned int>(n);
    unsigned int i = 3u, t = (unsigned int) sqrt(p) + 1u;
    if (p == 2u) {
        return reinterpret_cast<void*> (true);
    }
    if (p % 2u == 0u) {
        return reinterpret_cast<void*> (false);
    }

    while (i <= t) {
        if (p % i == 0u) {
            return reinterpret_cast<void*> (false);
        }
        i += 2u;
    }
    return reinterpret_cast<void*> (true);
}

int main()
{
    pthread_t t[8];
    bool primalities[8];
    for (int i = 0; i < 8; ++i) {
        pthread_create(&t[i], NULL, &isPrime, reinterpret_cast<void*>(i+2));
    }
    for (int i = 0; i < 8; ++i) {
        pthread_join(t[i], reinterpret_cast<void**>(&primalities[i]));
    }
    for (int i = 0; i < 8; ++i) {
        std::cout << primalities[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
