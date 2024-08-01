#include <memory/vmm.h>
#include <debug/assert.h>

#define PAGESIZE 4096

PageDirectory *currentDir;

static bool isAligned(uint32_t addr) {
    return (addr & (PAGESIZE - 1)) == 0;
}

int Paging::Map(uint32_t virt, uint32_t phys, bool user) {
    PageTable *table = nullptr;
    if (!isAligned(virt) || !(isAligned(phys))) {
        return -1;
    }
    
    uint32_t pdidx = (uint32_t)virt >> 22;
    uint32_t ptidx = (uint32_t)virt >> 12 & 0x3FF;
}

void Paging::SwitchPD(PageDirectory *pd) {
    ASSERT(pd);
    if (pd != nullptr) {
        currentDir = pd;
        asm volatile (
            "mov %0, %%cr3"
            :
            : "r"(pd)
            : "memory"
        );
    }
}