#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <signal.h>
#include "Handler.h"

namespace signalhandle {

using Handle = Handler::Handle;

struct Dispatcher {
    Dispatcher()
        : ancestor{}, handle{nullptr}
    {
    }
    Dispatcher(const Handle* hd)
        : ancestor{}, handle{hd}
    {
    }

    struct sigaction ancestor;
    const Handle* handle;
};

}

#endif
