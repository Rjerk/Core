#include <iostream>
#include <thread>
#include <atomic>

int n = 0;
std::atomic<int> a(0);

void addAtomically(int m)
{
    while (m--) {
        a.fetch_add(1);
    }
}

void Add(int m)
{
    while (m--) {
        ++n;
    }
}

int main()
{
    std::thread ts1[8], ts2[8];
    for (auto& t : ts1) {
        t = std::move(std::thread(addAtomically, 1000000));
    }
    for (auto& t : ts2) {
        t = std::move(std::thread(Add, 1000000));
    }
    for (auto& t : ts1) {
        t.join();
    }
    for (auto& t : ts2) {
        t.join();
    }
    std::cout << "a = " << a << std::endl;
    std::cout << "n = " << n << std::endl;
    return 0;
}
