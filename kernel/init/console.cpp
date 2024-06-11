//Early console code.

#include "console.h"
#include <stdint.h>

static volatile uint16_t *vidmem = (volatile uint16_t*)0xB8000;

struct cursor {
    int x, y;
};

static struct cursor cursor = {0, 0};

void kprint(const char *str) {
    while (*str != '\0') {
        kputc(*str);
        *str++;
    }
}

void kputc(char c) {
    switch (c) {
        case NEWLINE:
            cursor.x = 0;
            cursor.y++;
            break;
        default:
            vidmem[80 * cursor.y + cursor.x] = c | 0x0F << 8;
            cursor.x++;
    }
}