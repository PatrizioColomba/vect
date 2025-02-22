#include <stdio.h>
#include <stdlib.h>
#include "../vect.h"

int main(int argc, char** argv) {
    size_t size;
    printf("Enter the vector size: ");
    scanf("%zu", &size);
    int n1 = 4;
    int n2 = 13;
    int **vector = (int**)init_vect(size, (void*)&n1, (void*)&n2);

    if (vector == NULL) {
        printf("vector is null!\n");
        return -1;
    }

    printf("First vector (size %zu)\n", size);
    int** p = vector;
    for (int i = 0; i < size; i++) {
        printf("%d = %d\n", i, **p);
        *p++;
    }

    size_t* new_size = malloc(sizeof(size_t*));

    int** new_vector = (int**)append_vect((void**)vector, size, (void**)vector, size, new_size);    
    free_vect((void**)vector, size, NULL);

    printf("Second vector (size %zu)\n", *new_size);
    p = new_vector;
    for (int i = 0; i < *new_size; i++) {
        printf("%d = %d\n", i, **p);
        *p++;
    }

    p = NULL;

    return 0;
}