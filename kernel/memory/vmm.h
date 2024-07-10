#pragma once

#include <sys/defines.h>

namespace VirtMemory {
    namespace Page {
        int Map(uint32_t virt, uint32_t phys, bool user);
        void Free(uint32_t virt);
    }

    struct PageTable {
        uint32_t pages[1024];
    } __attribute__((packed));
}