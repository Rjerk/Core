#ifndef REGISTER_H
#define REGISTER_H

#include "Dispatcher.h"
#include <unordered_map>
#include <vector>
#include <thread>
#include <atomic>

namespace signalhandle {

using CallbackFunc = Handler::CallbackFunc;

class Register {
    using Dispvec = std::vector<Dispatcher>;
    using Handmap = std::unordered_map<int, Dispvec>;
    using Callmap = std::unordered_map<const Handle*, CallbackFunc>;
public:
    ~Register();

    static Register& instance()
    {
        return instance_;
    }

    template <typename CallbackFunc>
    Register& addHandler(const Handle*, CallbackFunc&&);

    Register& removeHandler(const Handle*);

    Register& push(int, const Handle*);
    Register& pop(int, const Handle*);

    void handle(int);

private:
    Register();
    void readSignal();

private:
    static Register instance_;
    Handmap handmap_;
    Callmap callmap_;
    int readfd_;
    int writefd_;
    std::thread thread_;
    std::atomic_bool running_;
};


}

#endif
