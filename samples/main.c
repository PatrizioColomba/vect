#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../vect.h"

bool is_equal_to_target(size_t index, void *element, void *target)
{
    printf("checking element at index %zu against target\n", index);
    return *(int *)element == *(int *)target;
}

int main(int argc, char **argv)
{
    size_t size;
    printf("Enter the vector size: ");
    scanf("%zu", &size);
    int n1 = 4;
    int n2 = 13;
    Vector *vector = init_vect(size, (void *)&n1, (void *)&n2);

    if (vector == NULL) {
        printf("vector is null!\n");
        return -1;
    }

    printf("First vector\n");
    PRINT_VECT_INT(vector);

    Vector *new_vector = append_vect(vector, vector);
    free_vect(vector, NULL);

    printf("Second vector\n");
    PRINT_VECT_INT(new_vector);

    int n3 = 42;
    Vector *expanded_vector = add_vect(new_vector, (void *)&n3);

    PRINT_VECT_INT(expanded_vector);

    int *an_element = (int *)get_vect(expanded_vector, 4);
    if (an_element != NULL) {
        printf("Element at index 4: %d\n", *an_element);
    } else {
        printf("Failed to get element at index 4\n");
    }

    int target;
    printf("Enter the number to find: ");
    scanf("%d", &target);

    size_t found_element_index = find_first_vect(
        expanded_vector, (bool (*)(size_t, void *, void *))is_equal_to_target,
        (void *)&target);
    if (found_element_index >= 0) {
        printf("Found element at index %zu: %d\n", found_element_index, *(int *)expanded_vector->data[found_element_index]);
    } else {
        printf("Element not found\n");
    }

    free_vect(expanded_vector, NULL);

    return 0;
}
