#include <arch/cpu/gdt.h>
#include <arch/cpu/idt.h>
#include <arch/init/console.h>
#include <arch/cpu/multiboot.h>
#include <memory/heap.h>
#include <tasking/scheduler.h>

extern "C" int kernel_init(multiboot_info_t *mbd) {
	kprint("Loading Red Planet\nSetting up CPU\n");

	GDT::Install();
	IDT::Install();

	// Hopefully 16 KiB is gonna be fine for kernel's heap.
	//Heap::Install(0x1000);

	//Process::Install();

	for (;;);
	return 0;
}