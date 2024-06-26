#pragma once

#include <stdint.h>

namespace PhysMemory {
    uint32_t AllocateBlock();
    void FreeBlock(uint32_t block);
    void Install(uint64_t memory_size);
}