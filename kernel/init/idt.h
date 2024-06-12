#pragma once

#include <stdint.h>

namespace IDT {
    struct Entry {
        uint16_t isr_low;
        uint16_t selector;
        uint8_t reserved;
        uint8_t attributes;
        uint16_t isr_high;
    } __attribute__((packed));

    void SetGate(uint16_t entry, void *interrupt, uint8_t flag);

    struct Pointer {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed));

    void Install();
}