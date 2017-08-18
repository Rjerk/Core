#ifndef HANDLER_H
#define HANDLER_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>

namespace signalhandle {

class Handler : boost::noncopyable {
public:
    using CallbackFunc = std::function<void (int)>;
    struct Handle;

private:
    template <typename T>
    Handler(T&& cb):
        Handler(CallbackFunc{std::forward<T>(cb)})
    {
    }

    Handler(Handler&&) = default;
    Handler& operator=(Handler&&) = default;

    Handler(CallbackFunc&&);

    ~Handler();

    Handler& addSignal(int);
    Handler& removeSignal(int);

    bool listenOn(int) const;

private:
    std::unique_ptr<Handle> handle_;
};

}

#endif
