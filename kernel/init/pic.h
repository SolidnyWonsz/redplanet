#pragma once

#include <init/asm.h>

namespace PIC {
	void ACK(unsigned char irq) {
		if (irq >= 8) {
			IO::outb(0xA0, 0x20);
		}
		IO::outb(0x20,0x20);
	}
}