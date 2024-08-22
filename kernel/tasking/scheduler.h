#include <library/cstdlib.h>

#pragma once

#include <common/limits.h>
#include <common/defines.h>

typedef int PID;

struct ProcessContext {
    uint32_t esp, ebp, eip;
    uint32_t esi, edi;
    uint32_t eax, ebx, ecx, edx;
    uint32_t eflags, cr3;
};

class Process {
    // Object methods
    public:
        void ElevatePrivilages();
        void Kill();
        PID GetPid();
        char *GetName();
        void Reparent(Process NewParent);

        enum {
            Unused = 0,
            Ready = 1,
            Running = 2,
            Waiting = 3,
            NoTask = 4      // To clarify:
                            // No task means process has been created, but
                            // there's no task assigned to it, so it will be
                            // allocated in memory, but it won't get scheduled.
        } State;
        ProcessContext Context;

    private:
        PID pid;
        char *Name;
        Process *Parent;
        bool isPriviliged;

    // Global methods
    public:
        static void Install();
        static void Schedule(Registers regs);
        static Process &Spawn(const char *name);

        static Process &Current();
        static Process &Init();
};