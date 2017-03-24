#include <iostream>
#include <mutex>
#include <thread>
#include <future>

unsigned long int calculateFactorial(short int n)
{
    unsigned long int r = 1;
    if (n > 20) {
        throw std::range_error("The number is too big.");
    }

    for (short int i = 2; i <= n; ++i) {
        r *= i;
    }
    return r;
}

int main()
{
    short int n = 20;
    // return future object
    std::future<unsigned long int> f = std::async(calculateFactorial, n);
    try {
        unsigned long int r = f.get();
        std::cout << n << "!= " << r << std::endl;
    } catch (const std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
