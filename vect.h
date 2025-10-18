#include <stddef.h>
#include <stdbool.h>

#ifndef __STRVECT_H__
#define __STRVECT_H__

#define DEBUG_LOG(fmt, ...) printf("DEBUG: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define PRINT_VECT_INT(vector)                                                 \
    printf("vector (size %zu)\n", vector->size);                               \
    for (size_t i = 0; i < vector->size; i++) {                                \
        printf("%zu = %d\n", i, *(int *)vector->data[i]);                      \
    }

typedef struct vect {
    void **data;
    size_t size;
} Vector;

Vector *init_vect(size_t n, ...);
void free_vect(Vector *vector, const void (*free_item)(void *));
Vector *append_vect(Vector *vector1, Vector *vector2);
Vector *add_vect(Vector *vector, void *element);
void *get_vect(Vector *vector, size_t index);
size_t find_first_vect(Vector *vector,
                       bool (*predicate)(size_t, void *, void *), void *target);
Vector *remove_vect(Vector *vector, size_t index,
                    const void (*free_item)(void *));

#endif

