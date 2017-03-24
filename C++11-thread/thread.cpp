#include <iostream>
#include <thread>

void threadFunc()
{
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread t(&threadFunc);
    t.join();

    return 0;
}
