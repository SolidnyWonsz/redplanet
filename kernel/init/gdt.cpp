#include "gdt.h"
#include "console.h"

#define BIT32 0xFFFFFFFF

extern "C" {
    extern void gdt_flush(); //Defined in kernel/init/boot.s
}

static GDT::Entry gdt[8];
static GDT::Pointer gdtr;

void GDT::SetGate(uint16_t entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt[entry].base_low = (base & 0xFFFF);
    gdt[entry].base_mid = (base >> 16) & 0xFF;
    gdt[entry].base_high = (base >> 24) & 0xFF;
    gdt[entry].limit = (limit & 0xFFFF);
    gdt[entry].flags = (limit >> 16) & 0x0F;
    gdt[entry].flags |= (flags & 0xF0);
    gdt[entry].access = access;
}

void GDT::Install() {
    kprint("Setting up GDT\n");
    gdtr.limit = (sizeof(GDT::Entry) * 6) - 1;
    gdtr.base = (uint32_t)&gdt;

    GDT::SetGate(0, 0, 0, 0, 0);
    GDT::SetGate(1, 0, BIT32, 0x9A, 0xCF);
    GDT::SetGate(2, 0, BIT32, 0x92, 0xCF);
    GDT::SetGate(3, 0, BIT32, 0xFA, 0xCF);
    GDT::SetGate(4, 0, BIT32, 0xF2, 0xCF);

    asm volatile("lgdt %0" : : "m"(gdtr));
    gdt_flush();
}