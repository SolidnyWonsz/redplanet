#include <init/idt.h>
#include <init/asm.h>

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

void IDT::Install() {
    idtr.base = (uintptr_t)&idt;
    idtr.limit = (uint16_t)sizeof(Entry) * 256 - 1;

    InstallPIC();

    IO::outb(0x21,0xfd);
    IO::outb(0xa1,0xff);

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}