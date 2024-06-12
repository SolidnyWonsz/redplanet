#include "idt.h"

static IDT::Entry idt[256];
static IDT::Pointer idtr;

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

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}