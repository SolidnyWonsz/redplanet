#pragma once

#include <stdint.h>

namespace Heap {
    void Initialize(uintptr_t startaddr);
    void *Allocate(uint32_t size);
    //void Free(void *block); // Not useful right now since the heap is very basic
}