#include <arch/cpu/exceptions.h>
#include <arch/cpu/idt.h>
#include <arch/init/console.h>
#include <arch/cpu/asm.h>

const char *exceptions[15] = {
    "Division by zero",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun", //We don't use this one
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault"
};

void Exception::Handler(Registers regs) {
    kprint("yoyoyoyo\n");
    //asm("cli; hlt");
    //for (;;);
}

void Exception::Install() {
    for (int i = 0; i < 16; i++) {
        IDT::SetGate(i, (void*)Exception::Handler, 0x8E);
    }
}