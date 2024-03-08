#include <stdint.h>

#define BIT64 0xFFFFFFFFFFFFFFFF

typedef struct gdtent_t {
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_mid2;
    uint32_t base_high;
} __attribute__((packed)) gdtent_t;

typedef struct gdtr_t {
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) gdtr_t;

__attribute__((aligned(0x10)))
static gdtent_t gdt[6];

static gdtr_t gdtr;

extern void load_gdtr(gdtr_t *gdtr);

static void gdt_set_gate(int entry, uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity) {
    gdt[entry].base_low = (uint16_t)base;
    gdt[entry].base_mid = (uint8_t)(base >> 16);
    gdt[entry].base_mid2 = (uint8_t)(base >> 24);
    gdt[entry].base_high = (base >> 32);
    gdt[entry].limit = (limit & 0xFFFF);
    gdt[entry].granularity = (limit >> 16) & 0x0F;
    gdt[entry].granularity |= (granularity & 0xF0);
    gdt[entry].access = access;
}

void gdt_install() {
    gdtr.size = (sizeof(gdtent_t) * 6) - 1;
    gdtr.offset = (uintptr_t)&gdt;

    gdt_set_gate(0,0,0,0,0);
    gdt_set_gate(1, 0, BIT64, 0x9A, 0xCF);
    gdt_set_gate(2, 0, BIT64, 0x92, 0xCF);
    gdt_set_gate(3, 0, BIT64, 0xFA, 0xCF);
    gdt_set_gate(4, 0, BIT64, 0xF2, 0xCF);

    load_gdtr(&gdtr);
}