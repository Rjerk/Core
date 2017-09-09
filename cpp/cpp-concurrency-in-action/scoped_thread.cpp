#include <thread>
#include <stdexcept>
#include <boost/noncopyable.hpp>

class ScopedThread : boost::noncopyable {
public:
    explicit ScopedThread(std::thread t)
        : t_(std::move(t))
    {
        if (!t_.joinable()) {
            throw std::logic_error{"No thread"};
        }
    }

    ~ScopedThread()
    {
        t_.join();
    }

private:
    std::thread t_;
};
