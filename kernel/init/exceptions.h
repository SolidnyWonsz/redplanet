#pragma once

#include <sys/defines.h>

namespace Exception {
void Handler(Registers regs);
void Install();
}