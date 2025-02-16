#include "vect.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void **init_vect(size_t n, ...) {
  if (n < 0) {
    printf("n must be grater than zero!\n");
    return NULL;
  }

  void **vector = malloc(n * sizeof(void **));
  va_list args;
  va_start(args, n);

  void **p = vector;
  for (int i = 0; i < n; i++) {
    *p = va_arg(args, void *);
    p++;
  }

  va_end(args);

  return vector;
}

void free_vect(void **vector, const size_t size,
               const void (*free_item)(void *)) {
  if (vector == NULL) {
    printf("parameter vector is null!\n");
    return;
  }

  if (free_item != NULL) {
    for (int i = 0; i < size; i++) {
      if (vector[i] != NULL)
        free_item(vector[i]);
    }
  }

  free(vector);
}

void **append_vect(void **vector, const size_t size, void **elements,
                   const size_t elements_size, size_t *new_size) {
  if (vector == NULL) {
    printf("parameter vector is null!\n");
    return NULL;
  }

  if (elements == NULL) {
    printf("parameter elements is null!\n");
    return NULL;
  }

  if (new_size == NULL) {
    printf("parameter new_size if null!\n");
    return NULL;
  }

  if (size < 0 || elements_size < 0) {
    printf("size %zu and elements_size %zu must be greater or equal than 0!\n");
    return NULL;
  }

  if (elements_size == 0) {
    *new_size = size;
    return vector;
  }

  if (size == 0) {
    *new_size = elements_size;
    return elements;
  }

  void **result_vector =
      (void **)malloc((size * elements_size) * sizeof(void *));

  for (int i = 0; i < size; i++) {
    result_vector[i] = vector[i];
  }

  for (int i = 0; i < elements_size; i++) {
    result_vector[size + i] = elements[i];
  }

  *new_size = size * elements_size;

  return result_vector;
}
