#include <device/serial.h>
#include <arch/asm.h>

#define PORT 0x3F8

int serial_install() {
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, 0x03);
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    outb(PORT + 4, 0x0B);
    outb(PORT + 4, 0x1E);
    outb(PORT + 0, 0xAE);

    if (inb(PORT + 0) != 0xAE) {
        return 1;
    }

    outb(PORT + 4, 0x0F);

    return 0;
}

void serial_putc(char c) {
    while ((inb(PORT + 5) & 0x20) == 0);
    outb(PORT, c);
    return;
}

void serial_puts(char *str) {
    while (*str != '\0') {
        serial_putc(*str);
        *str++;
    }
}