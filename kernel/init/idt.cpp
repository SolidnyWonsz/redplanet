#include <init/idt.h>
#include <init/asm.h>

static IDT::Entry idt[256];
static IDT::Pointer idtr;

static void InstallPIC() {
    outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
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
    idtr.limit = (uint16_t)sizeof(IDT::Entry) * 256 - 1;

    InstallPIC();

    outb(0x21,0xfd);
    outb(0xa1,0xff);

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}