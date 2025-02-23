#include <stdio.h>
#include <stdlib.h>
#include "../vect.h"

int main(int argc, char** argv) {
    size_t size;
    printf("Enter the vector size: ");
    scanf("%zu", &size);
    int n1 = 4;
    int n2 = 13;
    Vector *vector = init_vect(size, (void*)&n1, (void*)&n2);

    if (vector == NULL) {
        printf("vector is null!\n");
        return -1;
    }

    printf("First vector (size %zu)\n", vector->size);
    for (int i = 0; i < vector->size; i++) {
        printf("%d = %d\n", i, *(int*)vector->data[i]);
    }

    Vector *new_vector = append_vect(vector, vector);
    free_vect(vector, NULL);

    printf("Second vector (size %zu)\n", new_vector->size);
    for (int i = 0; i < new_vector->size; i++) {
        printf("%d = %d\n", i, *(int*)new_vector->data[i]);
    }

    free_vect(new_vector, NULL);

    return 0;
}