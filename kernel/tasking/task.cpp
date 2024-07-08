#include <tasking/scheduler.h>
#include <library/cstdlib.h>

using namespace Tasking;

static PID lastPid = 1;

static PID assignPid() {
    return lastPid++;
}

Task::Task(const char *name, bool ispriviliged) {
    pid = assignPid();
    memset(this->name, 0, PROC_MAXNAME);
    memcpy(this->name, name, sizeof(name));
    
    isPriviliged = false;

    Scheduler *scheduler = Scheduler::self();
    if (scheduler->CurrentTask() == nullptr) {
        parent = nullptr;
    } else {
        parent = scheduler->CurrentTask();
    }

    if (ispriviliged) {
        if (parent->isPriviliged) {
            isPriviliged = true;
        }
    }
}