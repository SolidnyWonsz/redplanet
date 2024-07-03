#pragma once

#define ASSERT(expr) \
    ((expr) ? (void)0 : kassert(#expr, __FILE__, __LINE__, __func__))

void kassert(const char *expr, const char *file, int line, const char *func);