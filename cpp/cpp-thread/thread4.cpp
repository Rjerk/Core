#include <iostream>
#include <thread>

class Worker {
public:
    Worker(int _a = 0, int _b = 0): a(_a), b(_b) { }
    void threadFunc()
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
            std::cout << a << " + " << b << " = " << a + b << std::endl;
    }
private:
    int a;
    int b;
};

int main()
{
    Worker worker(10, 20);
    std::thread t(std::bind(&Worker::threadFunc, &worker));
    t.join();
    return 0;
}
