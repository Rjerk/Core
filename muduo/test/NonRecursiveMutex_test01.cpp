#include "../mutex.h"

#include <vector>
#include <iostream>

class Foo {
public:
    void doit() const;
};

MutexLock mutex;
std::vector<Foo> foos;

void post(const Foo& f)
{
    MutexLockGuard lock(mutex);
    foos.push_back(f);
}

void traverse()
{
    MutexLockGuard lock(mutex);
    for (auto it = foos.begin(); it != foos.end(); ++it) {
        it->doit();
        std::cout << "size: " << foos.size() << std::endl;
    }
}

void Foo::doit() const
{
    Foo f;
    post(f);
}

int main()
{
    Foo f;
    post(f);
    traverse();
}
