#include "Handler.h"
#include "Register.h"
#include <set>

namespace signalhandle {

namespace {

using Sigset = std::set<int>;
using CallbackFunc = Handler::CallbackFunc;

};

struct Handler::Handle {
    Sigset sigset;
};

namespace {

using Handle = Handler::Handle;

}

Handler::Handler(CallbackFunc&& cb)
    : handle_{new Handle}
{
    Register::instance().addHandler(handle_.get(), std::move(cb));
}

Handler::~Handler()
{
    Register& reg = Register::instance();
    for (auto signal : handle_->sigset) {
        reg.pop(signal, handle_.get());
    }
    reg.removeHandler(handle_.get());
}

Handler& Handler::addSignal(int sig)
{
    if (handle_->sigset.find(sig) == handle_->sigset.cend()) {
        // add a new signal.
        Register::instance().push(sig, handle_.get());
        handle_->sigset.insert(sig);
    }
    return *this;
}

Handler& Handler::removeSignal(int sig)
{
    if (handle_->sigset.find(sig) != handle_->sigset.cend()) {
        // remove a signal in sigset.
        Register::instance().pop(sig, handle_.get());
        handle_->sigset.erase(sig);
    }
    return *this;
}

bool Handler::listenOn(int sig) const
{
    return handle_->sigset.find(sig) != handle_->sigset.cend();
}

}
