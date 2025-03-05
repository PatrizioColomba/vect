#include "vect.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Initializes a vector with a given number of elements.
 *
 * @param n The number of elements to initialize the vector with.
 * @param ... The elements to initialize the vector with.
 * @return A pointer to the initialized vector, or NULL if an error occurred.
 */
Vector *init_vect(size_t n, ...)
{
    void **data = malloc(n * sizeof(void *));
    if (data == NULL) {
        printf("failed to allocate memory for data!\n");
        return NULL;
    }

    va_list args;
    va_start(args, n);

    for (size_t i = 0; i < n; i++) {
        data[i] = va_arg(args, void *);
    }

    va_end(args);

    Vector *vect = malloc(sizeof(Vector));
    if (vect == NULL) {
        printf("failed to allocate memory for vector!\n");
        free(data);
        return NULL;
    }

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
 * @return A pointer to the new vector containing elements from both input
 * vectors, or NULL if an error occurred.
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

/**
 * @brief Adds an element into a vector.
 *
 * @param vector The vector to insert the element into.
 * @param element The element to insert.
 * @return A pointer to the new vector with the element inserted, or NULL if an
 * error occurred.
 */
Vector *add_vect(Vector *vector, void *element)
{
    if (vector == NULL) {
        printf("parameter vector is null!\n");
        return NULL;
    }

    size_t new_size = vector->size + 1;

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

    for (size_t i = 0; i < vector->size; i++) {
        result_vector->data[i] = vector->data[i];
    }

    result_vector->data[vector->size] = element;

    return result_vector;
}

/**
 * @brief Gets an element from a vector.
 *
 * @param vector The vector to get the element from.
 * @param index The index of the element to get.
 * @return A pointer to the element at the given index, or NULL if an error
 * occurred.
 */
void *get_vect(Vector *vector, size_t index)
{
    if (vector == NULL) {
        printf("parameter vector is null!\n");
        return NULL;
    }

    if (index >= vector->size) {
        printf("index is out of bounds!\n");
        return NULL;
    }

    return vector->data[index];
}

/**
 * @brief Finds the first element in the vector that satisfies the predicate
 * function.
 *
 * @param vector The vector to search.
 * @param predicate The predicate function to apply to each element.
 * @param target The target value to compare against.
 * @return The index of the first element that satisfies the predicate, or (size_t)-1
 * if no such element is found.
 */
size_t find_first_vect(Vector *vector, bool (*predicate)(size_t, void *, void *),
                      void *target)
{
    if (vector == NULL) {
        printf("parameter vector is null!\n");
        return (size_t)-1;
    }

    if (predicate == NULL) {
        printf("parameter predicate is null!\n");
        return (size_t)-1;
    }

    for (size_t i = 0; i < vector->size; i++) {
        if (predicate(i, vector->data[i], target)) {
            return i;
        }
    }

    return (size_t)-1;
}
