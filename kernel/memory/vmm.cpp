#include <memory/vmm.h>
#include <memory/pmm.h>

#define PAGESIZE 4096

static bool isAligned(uint32_t addr) {
    return (addr & (PAGESIZE - 1)) == 0;
}

int VirtMemory::Page::Map(uint32_t virt, uint32_t phys, bool user) {
    VirtMemory::PageTable *table = nullptr;
    if (!isAligned(virt) || !(isAligned(phys))) {
        return -1;
    }
    
    uint32_t pdidx = (uint32_t)virt >> 22;
    uint32_t ptidx = (uint32_t)virt >> 12 & 0x3FF;
}