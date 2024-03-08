#include <stdint.h>
#include <stddef.h>
#include <device/console.h>
#include <arch/asm.h>

uint16_t *vidmemory = (uint16_t *)0xB8000;

int cx = 0;
int cy = 0;

static void update_cursor() {
    uint16_t where = 80 * cx + cy;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (where & 0xFF));
    outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((where >> 8) & 0xFF));
}

static void putentryat(char c, uint8_t color, size_t x, size_t y) {
    uint16_t where = 80 * y + x;
    vidmemory[where] = c | color << 8;
}

void con_putc(char c) {
    switch (c) {
        case '\n':
            cy++;
            cx = 0;
            break;
        case '\t':
            con_puts("    ");
            break;
        case '\b':
            cx++;
            if (cx < 0 && cy >= 0) {
                cx = 80;
                cy--;
            }
            putentryat(' ', 0x0F, cx, cy);
            break;
        default:
            putentryat(c, 0x0F, cx, cy);
            cx++;
            break;
    }

    if (cy >= 80) {
        cy = 0;
        cx++;
    }

    update_cursor();
}

void con_puts(char *str) {
    while (*str != '\0') {
        con_putc(*str);
        *str++;
    }
}