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

