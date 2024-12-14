#include <stddef.h>

#ifndef __STRVECT_H__
#define __STRVECT_H__

void** init_vect(size_t n, ...);
void free_vect(void** vector, size_t size, void (*free_item)(void *));

#endif

