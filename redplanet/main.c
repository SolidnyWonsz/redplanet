#include <stdint.h>
#include <device/serial.h>
#include <arch/gdt.h>

void kernel_init() {
    for (;;);
    gdt_install();
    serial_putc('h');
}