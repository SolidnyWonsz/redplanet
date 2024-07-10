#include <memory/pmm.h>

#define MEMBLOCKSIZE 4096
#define BLKPERBCKT 8

#define SETBIT(i) bitmap[i / BLKPERBCKT] = bitmap[i / BLKPERBCKT] | (1 << (i % BLKPERBCKT))
#define CLEARBIT(i) bitmap[i / BLKPERBCKT] = bitmap[i / BLKPERBCKT] & (~(1 << (i % BLKPERBCKT)))
#define ISSET(i) ((bitmap[i / BLKPERBCKT] >> (i % BLKPERBCKT)) & 0x1)

extern uint8_t kernel_end[];
uint8_t *bitmap = (uint8_t*)(&kernel_end);
uint32_t total_block;

static uint32_t Find_Free_Block() {
    for (uint32_t i = 0; i < total_block; i++) {
        if (!ISSET(i)) {
            return i;
        }
    }
    return (uint32_t)-1;
}

uint32_t PhysMemory::AllocateBlock() {
    uint32_t freeblk = Find_Free_Block();
    SETBIT(freeblk);
    return freeblk;
}

void PhysMemory::FreeBlock(uint32_t block) {
    CLEARBIT(block);
}

void PhysMemory::Install(uint32_t memory_size) {
    total_block = memory_size / MEMBLOCKSIZE;
    uint32_t bmsz = total_block / BLKPERBCKT;

    if (bmsz * BLKPERBCKT < total_block) {
        bmsz++;
    }

    __builtin_memset(bitmap, 0, bmsz);
}