#include "vect.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector *init_vect(size_t n, ...) {
  if (n < 0) {
    printf("n must be grater than zero!\n");
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

void free_vect(Vector *vector, const void (*free_item)(void *)) {
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

    free(vector->data); // Libera i dati del vettore
    free(vector); // Libera la struttura del vettore
}

Vector *append_vect(Vector *vector1, Vector *vector2) {
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
    result_vector->data = malloc(new_size * sizeof(void *));
    result_vector->size = new_size;

    for (size_t i = 0; i < vector1->size; i++) {
        result_vector->data[i] = vector1->data[i];
    }

    for (size_t i = 0; i < vector2->size; i++) {
        result_vector->data[vector1->size + i] = vector2->data[i];
    }

    return result_vector;
}
