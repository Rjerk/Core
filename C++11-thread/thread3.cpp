#include <iostream>
#include <thread>

class Functor {
public:
    void operator()(int a, int b)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
        std::cout << a << " + " << b << " = " << a + b << std::endl;
    }
};

int main()
{
    int m = 10, n = 20;
    std::thread t(Functor(), m, n);
    t.join();
    return 0;
}
