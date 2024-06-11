#include <stdint.h>
#include "console.h"

extern "C" int kernel_init() {
	kprint("Loading Red Planet\n");
	return 0;
}