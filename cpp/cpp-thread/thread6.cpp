#include <iostream>
#include <mutex>
#include <thread>


template <typename T>
class Worker {
public:
    explicit Worker(int _no, T _a = 0, T _b = 0):
        no(_no), a(_a), b(_b) { }
    void threadFunc(T* r)
    {
        {
            std::lock_guard<std::mutex> locker(r); // constructor lock it.
            *r = a + b;
        } // locker auto lock using deconstructor.
        std::cout << "Thread No: " << no << std::endl;
        std::cout << a << " + " << b << " = " << a + b << std::endl;
    }
private:
    int no;
    T a;
    T b;
};

int main()
{
    return 0;
}
