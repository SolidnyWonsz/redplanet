#include <memory/heap.h>
#include <debug/assert.h>

bool heap_Initialized = false;
uintptr_t heap_CurrentAddr;

void Heap::Initialize(uintptr_t startaddr) {
    if (heap_Initialized) {
        ASSERT(!heap_Initialized);
        return;
    }

    heap_Initialized = true;
    heap_CurrentAddr = startaddr;
}

void *Heap::Allocate(uint32_t size) {
    heap_CurrentAddr += size;
    return heap_CurrentAddr - size;
}