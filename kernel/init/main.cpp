#include <init/gdt.h>
#include <init/idt.h>
#include <init/console.h>
#include <init/multiboot.h>
#include <memory/heap.h>
#include <tasking/scheduler.h>

extern "C" int kernel_init(multiboot_info_t *mbd) {
	kprint("Loading Red Planet\nSetting up CPU\n");

	GDT::Install();
	IDT::Install();

	// Hopefully 16 KiB is gonna be fine for kernel's heap.
	Heap::Install(0x1000);

	//Process::Install();

	for (;;);
	return 0;
}