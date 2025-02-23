#include "vect.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Initializes a vector with a given number of elements.
 *
 * @param n The number of elements to initialize the vector with.
 * @param ... The elements to initialize the vector with.
 * @return A pointer to the initialized vector, or NULL if an error occurred.
 */
Vector *init_vect(size_t n, ...)
{
    if (n < 0) {
        printf("n must be greater than zero!\n");
        return NULL;
    }

    void **data = malloc(n * sizeof(void **));
    va_list args;
    va_start(args, n);

    void **p = data;
    for (int i = 0; i < n; i++) {
        *p = va_arg(args, void *);
        p++;
    }

    va_end(args);

    Vector *vect = malloc(sizeof(Vector));
    vect->data = data;
    vect->size = n;

    return vect;
}

/**
 * @brief Frees the memory allocated for a vector.
 *
 * @param vector The vector to free.
 * @param free_item A function pointer to free individual items in the vector.
 */
void free_vect(Vector *vector, const void (*free_item)(void *))
{
    if (vector == NULL) {
        printf("parameter vector is null!\n");
        return;
    }

    if (free_item != NULL) {
        for (size_t i = 0; i < vector->size; i++) {
            if (vector->data[i] != NULL)
                free_item(vector->data[i]);
        }
    }

    free(vector->data);
    free(vector);
}

/**
 * @brief Appends two vectors into a new vector.
 *
 * @param vector1 The first vector.
 * @param vector2 The second vector.
 * @return A pointer to the new vector containing elements from both input vectors, or NULL if an error occurred.
 */
Vector *append_vect(Vector *vector1, Vector *vector2)
{
    if (vector1 == NULL) {
        printf("parameter vector1 is null!\n");
        return NULL;
    }

    if (vector2 == NULL) {
        printf("parameter vector2 is null!\n");
        return NULL;
    }

    if (vector1->size <= 0) {
        printf("vector1 size is zero or negative!\n");
        return NULL;
    }

    if (vector2->size <= 0) {
        printf("vector2 size is zero or negative!\n");
        return NULL;
    }

    size_t new_size = vector1->size + vector2->size;

    Vector *result_vector = malloc(sizeof(Vector));
    if (result_vector == NULL) {
        printf("failed to allocate memory for result_vector!\n");
        return NULL;
    }

    result_vector->data = malloc(new_size * sizeof(void *));
    if (result_vector->data == NULL) {
        printf("failed to allocate memory for result_vector data!\n");
        free(result_vector);
        return NULL;
    }

    result_vector->size = new_size;

    for (size_t i = 0; i < vector1->size; i++) {
        result_vector->data[i] = vector1->data[i];
    }

    for (size_t i = 0; i < vector2->size; i++) {
        result_vector->data[vector1->size + i] = vector2->data[i];
    }

    return result_vector;
}
