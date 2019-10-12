#include <stdio.h>
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

    for (int i = 0; i < size; i++) {
        printf("%d = %d\n", i, **vector);
        *vector++;
    }

    return 0;
}