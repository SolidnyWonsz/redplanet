#pragma once

#include <stdint.h>

namespace GDT {
    struct Entry {
        uint16_t limit;
        uint16_t base_low;
        uint8_t base_mid;
        uint8_t access;
        uint8_t flags;
        uint8_t base_high;
    } __attribute__((packed));
    
    void SetGate(uint16_t entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

    struct Pointer {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed));

    void Install();
}