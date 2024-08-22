#include <arch/cpu/pic.h>
#include <arch/cpu/asm.h>
#include <common/defines.h>

void PIC::ACK(uint8_t irq) {
    if (irq >= 8) {
		IO::outb(0xA0, 0x20);
	}
	IO::outb(0x20,0x20);
}