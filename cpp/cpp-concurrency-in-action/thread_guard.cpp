#include <thread>
#include <stdexcept>
#include <boost/noncopyable.hpp>

class ThreadGuard : boost::noncopyable {
public:
    explicit ThreadGuard(std::thread& t)
        : t_(t)
    {
    }

    ~ThreadGuard()
    {
        if (t_.joinable()) {
            t_.join();
        }
    }

private:
    std::thread& t_;

};
