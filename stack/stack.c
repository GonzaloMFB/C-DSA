#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int max_length;
    int count;
    int* array;
} Stack;

Stack* create_stack(int size) {
    Stack* stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "MALLOC ERROR - Could not allocate %lu bytes.", sizeof(Stack));
        return NULL;
    }
    stack->max_length = size;
    stack->count = 0;
    stack->array = malloc(size*sizeof(int));
    if (stack->array == NULL) {
        fprintf(stderr, "MALLOC ERROR - Could not allocate %lu bytes.", size*sizeof(int));
        free(stack);
        return NULL;
    }
    return stack;
}

void resize(Stack* stack) {
    // Doubles stack size
    if (stack == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Stack*.");
        return;
    }
    stack->max_length *= 2;
    int* new_arr = malloc(stack->max_length*sizeof(int));
    if (new_arr == NULL) {
        fprintf(stderr, "MALLOC ERROR - Could not allocate %lu bytes.", stack->max_length*sizeof(int));
        return;
    }
    for (int i = 0; i < stack->count; i++) {
       new_arr[i] = stack->array[i];
    }
    free(stack->array);
    stack->array = new_arr;
}

void destroy(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Stack*.");
        return;
    }
    free(stack->array);
    free(stack);
    stack = NULL;
}

void push(int val, Stack* stack) {
    // Add element at the end of the array and increase count.
    if (stack == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Stack*.");
        return;
    }
    // Shift all to right, meaning we go from right to left.
    
    // Increment stack->count now for proper shifting.
    stack->array[stack->count] = val;
    (stack->count)++;
    if (stack->count >= 0.7 * stack->max_length) {
        resize(stack);
    }
}

void pop(Stack* stack) {
    // Shift all to left, decrease count.
    if (stack == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Stack*.");
        return;
    }
    if (is_empty(stack) == 1) {
        return;
    }
    (stack->count)--;
}

int is_empty(Stack* stack) {
    // Return False (0) if not empty, 1 (True) if empty, -1 if error.
    if (stack == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Stack*.");
        return -1;
    }
    if (stack->count > 0) return 0;
    return 1;
}

int* peek(Stack* stack) {
    // Returning int pointer for convenience with error handling.
    // User must dereference.
    if (stack == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Stack*.");
        return NULL;
    }
    if (is_empty(stack) == 0) {
        return &(stack->array[(stack->count)-1]);
    }
    return NULL;
}