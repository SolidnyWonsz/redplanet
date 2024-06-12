#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include "console.h"

extern "C" int kernel_init() {
	kprint("Loading Red Planet\nSetting up CPU\n");
	GDT::Install();
	IDT::Install();
	return 0;
}