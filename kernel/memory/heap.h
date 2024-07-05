#pragma once

#include <stddef.h>
#include <stdint.h>

#define FREE 0
#define USED 1

#define ALIGNED(x) (!(x & 0x3))

namespace Heap {
    void Install(uint32_t size);
    void *Allocate(uint32_t size);
    //void Free(void *block); // Not useful right now since the heap is very basic
}

void *operator new(size_t size);