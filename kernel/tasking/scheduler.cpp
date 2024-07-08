#include <tasking/scheduler.h>

using namespace Tasking;

static Task init("init", true);

void Scheduler::Initialize() {
    currentTask = &init;
}

void Scheduler::Schedule() {

}

Task *Scheduler::CurrentTask() {
    return currentTask;
}