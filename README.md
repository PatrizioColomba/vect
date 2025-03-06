# vect

`vect` is a simple C library for managing dynamic arrays (vectors). It provides functions to initialize, append, add, get, find, and remove elements in a vector.

## Features

- Initialize a vector with a given number of elements
- Append two vectors into a new vector
- Add an element to a vector
- Get an element from a vector by index
- Find the first element in a vector that satisfies a predicate function
- Remove an element from a vector by index

## Installation

To use the `vect` library in your project, simply include the `vect.h` and `vect.c` files in your project.

## Usage

Here is an example of how to use the `vect` library:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vect.h"

bool is_equal_to_target(size_t index, void *element, void *target) {
    printf("checking element at index %zu against target\n", index);
    return *(int *)element == *(int *)target;
}

int main(int argc, char **argv) {
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
    if (found_element_index != (size_t)-1) {
        printf("Found element at index %zu: %d\n", found_element_index,
               *(int *)expanded_vector->data[found_element_index]);
    } else {
        printf("Element not found\n");
    }

    printf("\nTesting remove operation:\n");
    size_t remove_index;
    printf("Enter index to remove (0-%zu): ", expanded_vector->size - 1);
    scanf("%zu", &remove_index);

    Vector *reduced_vector = remove_vect(expanded_vector, remove_index, NULL);
    if (reduced_vector != NULL) {
        printf("Vector after removing element at index %zu:\n", remove_index);
        PRINT_VECT_INT(reduced_vector);
        free_vect(expanded_vector, NULL);
        expanded_vector = reduced_vector;
    }

    free_vect(expanded_vector, NULL);
    return 0;
}
```

## Example Output

```
Enter the vector size: 3
First vector
[4, 13, 0]
Second vector
[4, 13, 0, 4, 13, 0]
[4, 13, 0, 4, 13, 0, 42]
Element at index 4: 13
Enter the number to find: 13
checking element at index 0 against target
checking element at index 1 against target
Found element at index 1: 13

Testing remove operation:
Enter index to remove (0-6): 1
Vector after removing element at index 1:
[4, 0, 4, 13, 0, 42]
```
