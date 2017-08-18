#include "Register.h"
#include "Utility.h"

#include <fcntl.h>
#include <sys/select.h>
#include <strings.h>

namespace signalhandle {

namespace {

constexpr size_t maxerrors{5};

constexpr uint8_t signum = std::numeric_limits<uint8_t>::max();

void catchSignal(int sig)
{
    Register::instance().handle(sig);
}

}

Register Register::instance_{};

Register::Register()
    : handmap_{}, callmap_{}, readfd_{-1},
      writefd_{-1}, thread_{}, running_{true}
{
    int fds[2];
    if (::pipe(fds) != 0) {
        throw std::runtime_error{"Cannot create a pipe for signals."};
    }

    readfd_ = fds[0];
    writefd_ = fds[1];

    fdutils::setNonblock(readfd_);
    fdutils::setCloexec(writefd_);
    fdutils::setNonblock(writefd_);

    thread_ = std::thread{&Register::readSignal, this};
}

Register::~Register()
{
    running_.exchange(false);

    size_t i = 0;
    while (i < maxerrors &&
           fdutils::write(writefd_, &signum, sizeof(signum)) != sizeof(signum)) {
        ++i;
    }
    thread_.join();
    fdutils::close(readfd_);
    fdutils::close(writefd_);
}

template <typename CallbackFunc>
Register& Register::addHandler(const Handle* hd, CallbackFunc&& func)
{
    callmap_.emplace(hd, std::forward<CallbackFunc>(func));
    return *this;
}

Register& Register::removeHandler(const Handle* hd)
{
    callmap_.erase(hd);
    return *this;
}

Register& Register::push(int sig, const Handle* hd)
{
    struct sigaction action;
    ::bzero(&action, sizeof(action));
    action.sa_handler = &catchSignal;
    action.sa_flags = 0;
    ::sigfillset(&action.sa_mask);

    Dispatcher dp{hd};

    if (::sigaction(sig, &action, &dp.ancestor) < 0) {
        throw std::runtime_error{"sigaction() error"};
    }

    auto iter = handmap_.find(sig);
    if (iter == handmap_.end()) {
        iter = handmap_.emplace(sig, Dispatcher{}).first;
    }

    Dispvec& dispvec = iter->second;
    dispvec.push_back(std::move(dp));

    return *this;
}

Register& Register::pop(int sig, const Handle* hd)
{
    auto dispvec_ptr = handmap_.find(sig);
    if (dispvec_ptr != handmap_.end()) {
        Dispvec& iter = dispvec_ptr->second;
        // find signal and set sigaction.
    }
    return *this;
}

void Register::handle(int sig)
{
    uint8_t reduced = static_cast<uint8_t>(sig);
    size_t i = 0;
    while (i < maxerrors
            && fdutils::write(writefd_, &reduced, sizeof(reduced)) != sizeof(reduced)) {
        ++i;
    }
}

}
