#include <library/cstring.h>
#include <debug/assert.h>

extern "C" {

int strlen(const char *str) {
    char *_str = (char*)str;
    int len = 0;
    for (char *c = &_str[0]; *c != '\0'; c++, len++);
    return len;
}

char *itoa(int n, char *buf, int base) {
    char *p = buf + 20;

    if (n >= 0) {
        do {
            *--p = '0' + (n % base);
            n /= base;
        } while (n != 0);

        return p;
    } else {
        do {
            *--p = '0' - (n % base);
            n /= base;
        } while (n != 0);

        *--p = '-';
    }

    return p;
}

}