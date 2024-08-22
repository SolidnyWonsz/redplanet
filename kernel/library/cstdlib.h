#pragma once

#include <common/defines.h>

extern "C" {

void *memmove(void *dstptr, const void * srcptr, size_t size);
void* memcpy(void *dstptr, const void *srcptr, size_t size);
void* memset(void* bufptr, int value, size_t size);
int memcmp(const void *ptr1, const void *ptr2, size_t size);

}