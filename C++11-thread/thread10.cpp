#include <iostream>
#include <vector>
#include <tuple>
#include <mutex>
#include <thread>

std::mutex x;

template <typename T>
class Worker {
public:
    explicit Worker(int _no, T _a = 0, T _b = 0):
        no(_no), a(_a), b(_b) { }
    void threadFunc(T* r)
    {
        x.lock();
        *r = a + b;
        x.unlock();
    }
private:
    int no;
    T a;
    T b;
};

int main()
{
    std::vector<std::tuple<Worker<int>*, int, std::thread*>> v(8);

    for (int i = 0; i < 8; ++i) {
        v[i] = std::make_tuple(new Worker<int>(i, i+1, i+2), 0, nullptr);
    }

    for (int i = 0; i < 8; ++i) {
        std::cout << "NO. " << i << ": result = " << std::get<1>(v[i]) << std::endl;
    }

    for (int i = 0; i < 8; ++i) {
        auto f = std::bind(&Worker<int>::threadFunc, std::get<0>(v[i]), std::placeholders::_1);
        std::get<2>(v[i]) = new std::thread(f, &std::get<1>(v[i]));
    }

    for (int i = 0; i < 8; ++i) {
        std::get<2>(v[i])->join();
        delete std::get<0>(v[i]);
        std::get<0>(v[i]) = nullptr;
        delete std::get<2>(v[i]);
        std::get<2>(v[i]) = nullptr;
    }

    for (int i = 0; i < 8; ++i) {
        std::cout << "NO. " << i << ": result = " << std::get<1>(v[i]) << std::endl;
    }
    return 0;
}
