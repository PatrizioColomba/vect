#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "vect.h"

void** init_vect(size_t n, ...) {
	if (n <= 0) {
		return NULL;
	}

	void** vector = malloc(n * sizeof(void**)); 
	va_list args;
    va_start(args, n); 

	void** p = vector;
	for(int i = 0; i < n; i++) {
		*p = va_arg(args, void *);
		p++; 
	}

	va_end(args);

	return vector;
}

void free_vect(void** vector, size_t size, void (*free_item)(void*)) {
	if (vector == NULL) {
		return;
	}

	if (free_item != NULL) {
		for(int i = 0; i < size; i++) {
			if (vector[i] != NULL) free_item(vector[i]);
		}
	}

	free(vector);
}

