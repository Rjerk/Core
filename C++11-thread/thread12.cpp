#include <iostream>
#include <future>
#include <thread>
#include <exception>

unsigned long int calculateFactorial(short int n)
{
    unsigned long int r = 1;
    if (n > 20) {
        throw std::range_error("The number is too big");
    }

    for (short int i = 2; i <= n; ++i) {
        r *= i;
    }
    return r;
}

void doCalculateFactorial(std::promise<unsigned long int>&& promise, short int n)
{
    try {
        promise.set_value(calculateFactorial(n));
    } catch(std::range_error&) {
        promise.set_exception(std::current_exception());
    }
}

int main()
{
    short int n = 6;
    std::promise<unsigned long int> p; // create promise object
    std::future<unsigned long int> f = p.get_future(); // obtain future object
    std::thread t(doCalculateFactorial, std::move(p), n);

    t.detach();
    try {
        unsigned long int r = f.get();
        std::cout << n << "!= " << r << std::endl;
    } catch (std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
