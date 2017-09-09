#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

std::mutex x;
std::condition_variable cond;
bool ready = false;

bool isReady()
{
    return ready;
}

void Run(int no)
{
    std::unique_lock<std::mutex> locker(x);
    while (!ready) {
        cond.wait(locker);
    }
    // three-line code is equal to cond.wait(locker, &isReady)
    std::cout << "thread " << no << std::endl;
}

int main()
{
    std::thread threads[8];
    for (int i = 0; i < 8; ++i) {
        threads[i] = std::thread(Run, i);
    }
    std::cout << "8 threads ready..." << std::endl;
    {
        std::unique_lock<std::mutex> locker(x);
        ready = true;
        cond.notify_all();
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
