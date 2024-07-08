#pragma once

#include <sys/limits.h>

typedef int PID;

namespace Tasking {
    class Task {
        public:
            Task(const char *name, bool ispriviliged);
            ~Task();

            void ElevatePrivilages();
            void Kill();

            PID GetPid();
            char *GetName();

            void Reparent(Task *NewParent);
        private:
            PID pid;
            char name[PROC_MAXNAME];
            Task *parent;

            bool isPriviliged;
    };

    class Scheduler {
        public:
            Scheduler(Scheduler &other) = delete;

            static Scheduler *self() {
                return &_scheduler;
            }

            Task *CurrentTask();

            void Initialize();
            void Schedule();

        private:
            Scheduler() {}
            ~Scheduler() {}

            static Scheduler _scheduler;
            Task *currentTask;
    };
}