#pragma once

#include <common/defines.h>

#define IRQBASE 31

class IDT {
    public:
        static void Install();
        static void SetGate(uint16_t entry, void *interrupt, uint8_t flag);
};