#include <stddef.h>

#ifndef __STRVECT_H__
#define __STRVECT_H__

typedef struct vect {
    void **data;
    size_t size;
} Vector;
Vector *init_vect(size_t n, ...);
void free_vect(Vector *vector, const void (*free_item)(void *));
Vector *append_vect(Vector *vector1, Vector *vector2);

#endif
