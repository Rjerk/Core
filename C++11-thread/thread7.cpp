#include <iostream>
#include <mutex>
#include <thread>

class Account {
public:
    explicit Account(double _balance): balance(_balance) { }
    double getBalance() { return balance; }
    void Increase(double amount) { balance += amount; }
    void Decrease(double amount) { balance -= amount; }
    std::mutex& getMutex() { return x; }
private:
    double balance;
    std::mutex x;
};

void Transfer(Account& from, Account& to, double amount)
{
    std::unique_lock<std::mutex> locker1(from.getMutex(), std::adopt_lock);
    std::unique_lock<std::mutex> locker2(to.getMutex(), std::adopt_lock);
    std::lock(from.getMutex(), to.getMutex());
    from.Decrease(amount);
    to.Increase(amount);
}

int main()
{
    Account a1(100.0);
    Account a2(200.0);

    // thread arguments use pass-value, use std::ref() use pass-reference.
    std::thread t1(Transfer, std::ref(a1), std::ref(a2), 10.0);
    std::thread t2(Transfer, std::ref(a2), std::ref(a1), 20.0);
    t1.join();
    t2.join();
    std::cout << "a1: " << a1.getBalance() << std::endl;
    std::cout << "a2: " << a2.getBalance() << std::endl;
    return 0;
}
