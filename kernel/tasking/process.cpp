#include <tasking/scheduler.h>
#include <library/cstdlib.h>

void Process::ElevatePrivilages() {
    if (Parent) {
        if (Parent->isPriviliged) {
            isPriviliged = true;
        }
    }
}