#include <memory/heap.h>
#include <debug/assert.h>
#include <init/console.h>

// I know the code doesn't look or work very well but I'm still
// pretty much a noob with C++. I'm more of a C guy, ya know.
//
// Jumping into OS Dev without prior C++ knowledge
// was a mistake I guess...

extern uint8_t kernel_end[];

struct KernelHeap {
    static bool Initialized;
    static uint32_t *StartAddr, *EndAddr;
    // One bit represents one 4 byte memory block
    static uint8_t *Bitmap;
    static uint32_t MemoryBlockSize;
};

bool KernelHeap::Initialized = false;
uint32_t *KernelHeap::StartAddr = 0;
uint32_t *KernelHeap::EndAddr = 0;
uint8_t *KernelHeap::Bitmap = nullptr;
uint32_t KernelHeap::MemoryBlockSize = 4; // Just 4 bytes

uint32_t TotalSize;

static uint32_t FindFreeBlocks(uint16_t blocks) {
    int FoundBlocks = 0;

    for (uint32_t i = 0; i < TotalSize; ++i) {
        if (!((KernelHeap::Bitmap[i/8] >> (i % 8)) & 0x1)) {
            FoundBlocks++;
            if (FoundBlocks == blocks) {
                return i - blocks + 1;
            }
        } else {
            FoundBlocks = 0;
        }
    }

    return (uint32_t)-1;
}

void Heap::Install(uint32_t size) {
    if (KernelHeap::Initialized) {
        ASSERT(!KernelHeap::Initialized);
        return;
    }

    kprint("Setting up KHeap\n");
    KernelHeap::Initialized = true;
    KernelHeap::StartAddr = (uintptr_t*)&kernel_end;
    KernelHeap::EndAddr = KernelHeap::StartAddr + size + 1025; // It points to memory address after the bitmap
    TotalSize = size / KernelHeap::MemoryBlockSize;

    KernelHeap::Bitmap = (uint8_t*)(&kernel_end);
}

void *Heap::Allocate(size_t size) {
    int TotalBlockCount;

    float fBlocksCount = size / 4;
    int iBlocksCount = fBlocksCount;
    if ((float)iBlocksCount != fBlocksCount) {
        TotalBlockCount = fBlocksCount + 1;
    } else {
        TotalBlockCount = fBlocksCount;
    }
    // The circus happening above is supposed to calculate amount of blocks
    // to allocate and in case the number has floating point, we must round down
    // the block count. Not very ideal ceil() implementation, but it does the job.
    // (Sorry if the explanation is unclear, I'm very sleepy atm)
    uint32_t FreeBlock = FindFreeBlocks(TotalBlockCount);
    if (FreeBlock == (uint32_t)-1) {
        ASSERT(FreeBlock > 0);
        return nullptr;
    }

    KernelHeap::Bitmap[FreeBlock/8] = KernelHeap::Bitmap[FreeBlock/8] | (1 << (FreeBlock % 8));
    return (void*)(KernelHeap::StartAddr + (FreeBlock * 4));
}

void Heap::Free(void *block) {
    uint32_t *UsedBlock = (uint32_t*)(((uintptr_t)block - (uintptr_t)KernelHeap::EndAddr) / 4);
    KernelHeap::Bitmap[(uintptr_t)UsedBlock/8] = KernelHeap::Bitmap[(uintptr_t)UsedBlock/8] & (~(1 << ((uintptr_t)UsedBlock % 8)));
}

void *operator new(size_t size) {
    void *ptr = Heap::Allocate(size);
    return ptr;
}

void operator delete(void *p) {
    Heap::Free(p);
}