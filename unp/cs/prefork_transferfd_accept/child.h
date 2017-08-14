#ifndef CHILD_H
#define CHILD_H

#include <wait.h>

using Child = struct {
    pid_t child_pid;
    int   child_pipefd; // parent's stream pipe to/from child.
    int   child_status; // 0 = ready.
    long  child_count; // # connections handled.
};

Child* cptr = nullptr;

#endif
