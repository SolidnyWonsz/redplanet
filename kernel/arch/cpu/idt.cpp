#include <arch/cpu/idt.h>
#include <arch/cpu/asm.h>
#include <arch/cpu/pic.h>
#include <timer/timer.h>
#include <arch/init/console.h>
#include <arch/cpu/exceptions.h>

static struct Entry {
    uint16_t isr_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;
} __attribute__((packed)) idt[256];

static struct Pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr;

static void InstallPIC() {
    IO::outb(0x20, 0x11);
	IO::outb(0xA0, 0x11);
	IO::outb(0x21, 0x20);
	IO::outb(0xA1, 0x28);
	IO::outb(0x21, 0x04);
	IO::outb(0xA1, 0x02);
	IO::outb(0x21, 0x01);
	IO::outb(0xA1, 0x01);
	IO::outb(0x21, 0x0);
	IO::outb(0xA1, 0x0);
}

void IDT::SetGate(uint16_t entry, void *interrupt, uint8_t flag) {
    idt[entry].isr_low = (uint32_t)interrupt & 0xFFFF;
    idt[entry].isr_high = (uint32_t)interrupt >> 16;
    idt[entry].attributes = flag;
    idt[entry].selector = 0x08;
    idt[entry].reserved = 0;
}

char map_us[0x100] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static void KeyboardHandler() {
    IRQ_ENTER;
    char c = IO::inb(0x60);
    kputc(map_us[c]);
    PIC::ACK(1);
    asm("popa");
    asm("leave");
    asm("iret");
}

void IDT::Install() {
    idtr.base = (uintptr_t)&idt;
    idtr.limit = (uint16_t)sizeof(Entry) * 256 - 1;

    InstallPIC();
    Exception::Install();

    IO::outb(0x21,0xfd);
    IO::outb(0xa1,0xff);

    //IDT::SetGate(32, (void*)Timer::Handler, 0x8E);
    IDT::SetGate(33, (void*)KeyboardHandler, 0x8E);

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}