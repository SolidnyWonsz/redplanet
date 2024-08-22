#pragma once

#include <arch/cpu/asm.h>

namespace PIC {
	void ACK(unsigned char irq);
}