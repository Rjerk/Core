#include <iostream>
#include <pthread.h>

class InfoPrinted {
public:
    InfoPrinted(char _c, int _n): c(_c), n(_n) { }
    void show() const
    {
        for (int i = 0; i < n; ++i) {
            std::cerr << c;
        }
    }
private:
    char c;
    int n;
};

void* printInfo(void* info)
{
    InfoPrinted* p = reinterpret_cast<InfoPrinted*>(info);
    if (p) {
        p->show();
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    InfoPrinted* p = new InfoPrinted('a', 100);
    pthread_create(&t1, NULL, &printInfo, reinterpret_cast<void*>(p));

    InfoPrinted* q = new InfoPrinted('z', 100);
    pthread_create(&t2, NULL, &printInfo, reinterpret_cast<void*>(q));

    // wait child-threads finish.
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
