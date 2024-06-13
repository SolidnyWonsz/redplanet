#include "gdt.h"
#include "idt.h"
#include "console.h"
#include "multiboot.h"
#include <memory/pmm.h>

extern "C" int kernel_init(multiboot_info_t *mbd) {
	kprint("Loading Red Planet\nSetting up CPU\n");

	GDT::Install();
	IDT::Install();

	if (!(mbd->flags >> 6 & 0x1)) {
		kprint("Invalid memory map\n");
	}

	for (int i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
		multiboot_memory_map_t *mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr+i);
		if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
			PhysMemory::Install(mmmt->addr);
		}
	}

	for (;;);
	return 0;
}