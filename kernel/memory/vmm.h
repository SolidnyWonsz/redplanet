#pragma once

#include <common/defines.h>

struct PageTable {
    uint32_t pages[1024];
} __attribute__((packed));

struct PageDirectory {
    PageTable tables[1024];
} __attribute__((packed));

class Paging {
    public:
        static int Map(uint32_t virt, uint32_t phys, bool user);
        static void Free(uint32_t virt);

        static void SwitchPD(PageDirectory *pd);
};