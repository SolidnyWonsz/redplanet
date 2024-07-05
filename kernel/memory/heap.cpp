#include <memory/heap.h>
#include <init/console.h>
#include <library/cstring.h>
#include <debug/assert.h>

struct {
    bool Initialized = false;
    uintptr_t StartAddr, EndAddr;
    //One bit represents one 4 byte memory block
    struct {
        uint8_t MemoryBlock : 1;
    } BlockBitmap;
} KernelHeap;

extern uint8_t kernel_end[];

void Heap::Install(uint32_t size) {
    if (KernelHeap.Initialized) {
        ASSERT(!KernelHeap.Initialized);
        return;
    }

    KernelHeap.Initialized = true;
    KernelHeap.StartAddr = (uintptr_t)kernel_end;
    KernelHeap.EndAddr = KernelHeap.StartAddr + sizeof(HeapBlock);

    KernelHeap.BlockBitmap = (uint8_t*)(&kernel_end);
}

void *Heap::Allocate(uint32_t size) {

}

//void Heap::Free(void *block) {

//}

void *operator new(size_t size) {
    void *ptr = Heap::Allocate(size);
    return ptr;
}