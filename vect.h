#include <stddef.h>

#ifndef __STRVECT_H__
#define __STRVECT_H__

void **init_vect(size_t n, ...);
void free_vect(void **vector, const size_t size,
               const void (*free_item)(void *));
void **append_vect(void **vector, const size_t vector_size, void **elements,
                   const size_t elements_size, size_t *new_size);

#endif
