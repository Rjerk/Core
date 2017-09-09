#include <iostream>
#include <functional>

using CallbackFunc = std::function<void (int)>;

class EventHandler {
public:
    void addHandler(CallbackFunc cb)
    {
        cb_ = cb;
    }

    void test()
    {
        cb_(10);
    }

private:
    CallbackFunc cb_;

};

EventHandler* handler = nullptr;

class MyClass {
public:
    MyClass()
    {
        private_x = 5;
        handler->addHandler( [&](int x) { std::cout << x + private_x << std::endl; } );
    }

    void Callback(int x)
    {
        std::cout << x + private_x << std::endl;
    }
private:
    int private_x;
};

int main()
{
    handler = new EventHandler();
    MyClass m;
    handler->test();
    handler->addHandler([](int a) { std::cout << "this is a test." << a; });
    handler->test();
}
