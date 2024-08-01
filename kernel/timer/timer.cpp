#include <timer/timer.h>
#include <init/asm.h>
#include <tasking/scheduler.h>
#include <init/pic.h>

void Timer::Handler(Registers regs) {
    IRQ_ENTER;
    //Process::Schedule(regs);
    PIC::ACK(0);
    IRQ_LEAVE;
}