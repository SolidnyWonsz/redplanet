#pragma once

#include <sys/defines.h>

#define FREE 0
#define USED 1

#define ALIGNED(x) (!(x & 0x3))

namespace Heap {
    void Install(uint32_t size);
    void *Allocate(size_t size);
    void Free(void *block);
}

void *operator new(size_t size);
void operator delete(void *block);