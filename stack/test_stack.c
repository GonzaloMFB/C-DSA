#include <stdio.h>
#include <assert.h>
#include "stack.h"

void test_create_stack() {
    Stack* stack = create_stack(5);
    assert(stack != NULL);
    assert(stack->max_length == 5);
    assert(stack->count == 0);
    assert(stack->array != NULL);
    destroy(stack);
    printf(" test_create_stack passed\n");
}

void test_push_single() {
    Stack* stack = create_stack(5);
    push(42, stack);
    assert(stack->count == 1);
    int* top = peek(stack);
    assert(*top == 42);
    destroy(stack);
    printf(" test_push_single passed\n");
}

void test_push_multiple() {
    Stack* stack = create_stack(5);
    push(1, stack);
    push(2, stack);
    push(3, stack);
    assert(stack->count == 3);
    int* top = peek(stack);
    assert(*top == 3);
    destroy(stack);
    printf(" test_push_multiple passed\n");
}

void test_pop() {
    Stack* stack = create_stack(5);
    push(1, stack);
    push(2, stack);
    push(3, stack);
    
    pop(stack);
    assert(stack->count == 2);
    int* top = peek(stack);
    assert(*top == 2);
    
    pop(stack);
    assert(stack->count == 1);
    top = peek(stack);
    assert(*top == 1);
    
    destroy(stack);
    printf(" test_pop passed\n");
}

void test_is_empty() {
    Stack* stack = create_stack(5);
    assert(is_empty(stack) == 1);
    
    push(42, stack);
    assert(is_empty(stack) == 0);
    
    pop(stack);
    assert(is_empty(stack) == 1);
    
    destroy(stack);
    printf(" test_is_empty passed\n");
}

void test_peek_empty() {
    Stack* stack = create_stack(5);
    int* result = peek(stack);
    assert(result == NULL);
    destroy(stack);
    printf(" test_peek_empty passed\n");
}

void test_pop_empty() {
    Stack* stack = create_stack(5);
    pop(stack);
    assert(stack->count == 0);
    destroy(stack);
    printf(" test_pop_empty passed\n");
}

void test_resize() {
    Stack* stack = create_stack(2);
    push(1, stack);
    push(2, stack);
    
    int original_max = stack->max_length;
    push(3, stack);
    
    assert(stack->max_length > original_max);
    assert(stack->count == 3);
    
    int* top = peek(stack);
    assert(*top == 3);
    
    destroy(stack);
    printf(" test_resize passed\n");
}

int main() {
    printf("Running stack tests...\n\n");
    
    test_create_stack();
    test_push_single();
    test_push_multiple();
    test_pop();
    test_is_empty();
    test_peek_empty();
    test_pop_empty();
    test_resize();
    
    printf("\n All tests passed!\n");
    return 0;
}