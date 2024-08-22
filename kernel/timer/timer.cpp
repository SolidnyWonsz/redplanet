#include <timer/timer.h>
#include <arch/cpu/asm.h>
#include <tasking/scheduler.h>
#include <arch/cpu/pic.h>

void Timer::Handler(Registers regs) {
    IRQ_ENTER;
    //Process::Schedule(regs);
    PIC::ACK(0);
    IRQ_LEAVE;
}