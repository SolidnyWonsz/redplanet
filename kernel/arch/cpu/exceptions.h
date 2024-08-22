#pragma once

#include <common/defines.h>

namespace Exception {
void Handler(Registers regs);
void Install();
}