#include <tasking/scheduler.h>
#include <arch/init/console.h>
#include <arch/cpu/idt.h>
#include <memory/vmm.h>
#include <library/array.h>
#include <arch/init/console.h>
#include <library/cstring.h>

// It's fixed sized array for now, just for testing.
// Once I'll have vector library ready, It'll be
// dynamically allocated.

LibCPP::Array<Process, 20> ProcessList;
Process *lastProcess;
int ProcessIndex;

Process *current;
Process *init;

static void ContextSwitch(ProcessContext &context, Registers regs) {
    if (lastProcess) {
        lastProcess->Context.eax = regs.eax;
        lastProcess->Context.ebx = regs.ebx;
        lastProcess->Context.ecx = regs.ecx;
        lastProcess->Context.edx = regs.edx;
        lastProcess->Context.esi = regs.esi;
        lastProcess->Context.edi = regs.edi;
        lastProcess->Context.ebp = regs.ebp;
        lastProcess->Context.esp = regs.esp;
        lastProcess->Context.eflags = regs.eflags;
        lastProcess->Context.eip = regs.eip;
        asm volatile(
            "mov %%cr3, %0"
            : "=r"(lastProcess->Context.cr3)
        );
    }

    if ((uint32_t*)context.cr3 != nullptr) {
        Paging::SwitchPD((PageDirectory*)context.cr3);
    }

    asm volatile (
        "movl %%esp, %0\n"
        "movl %%ebp, %1\n"
        "movl $1f, %2\n"
        "movl %%eax, %3\n"
        "movl %%ebx, %4\n"
        "movl %%ecx, %5\n"
        "movl %%edx, %6\n"
        "movl %%esi, %7\n"
        "movl %%edi, %8\n"
        "pushfl\n"
        "popl %9\n"
        "1:\n"
        :   "=m"(context.esp), "=m"(context.ebp), "=m"(context.eip),
            "=m"(context.eax), "=m"(context.ebx), "=m"(context.ecx),
            "=m"(context.edx), "=m"(context.esi), "=m"(context.edi),
            "=m"(context.eflags)
        :
        :   "memory"
    );
}

void Process::Install() {
    kprint("Setting up Scheduler\n");
    ProcessIndex = 0;
    Process::Init() = Spawn("init");
    Process::Current() = Process::Init();
    Spawn("test");
    lastProcess = nullptr;
}

void Process::Schedule(Registers regs) {
    kprint("Schedule\n");
    lastProcess = &Process::Current();
    while (bool Scheduling = true) {
        Process::Current() = ProcessList[++ProcessIndex];
        if (Process::Current().State == Ready) {
            kprint("Ready\n");
            ContextSwitch(Process::Current().Context, regs);
            Scheduling = false;
        }

        if (ProcessIndex > (int)ProcessList.size()) {
            ProcessIndex = 0;
        }
    }
    kprint("Schedule finished\n");
}

static PID lastPid = 1;

static PID AssignPid() {
    return lastPid++;
}

Process &Process::Spawn(const char *name) {
    kprint("Spawning ");
    kprint(name);
    kprint("\n");
    for (size_t i = 0; i < ProcessList.size(); i++) {
        Process &proc = ProcessList[i];
        if (proc.State == Unused) {
            kprint("Unused\n");
            proc.Name = (char*)name;
            proc.State = Ready;
            proc.pid = AssignPid();
            
            if (Current().Parent && Current().Parent->isPriviliged) {
                proc.isPriviliged = true;
            } else {
                proc.isPriviliged = false;
            }

            // 0x200 is interrupt enable flag
            proc.Context.eflags = 0x200;
            break;
        }
    }
}

Process &Process::Current() {
    return *current;
}

Process &Process::Init() {
    return *init;
}