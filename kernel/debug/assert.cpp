#include <debug/assert.h>
#include <init/console.h>

void kassert(const char *expr, const char *file, int line, const char *func) {
    asm volatile("cli");

    kprint("Assert failed!\nFile: ");
    kprint(file);
    kprint("\nFunction: ");
    kprint(func);
    kprint("\n");

    for (;;) {
        asm volatile("hlt");
    }
}