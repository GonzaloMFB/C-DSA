#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    int max_length;
    int count;
    int* array;
} Stack;

Stack* create_stack(int size);
void resize(Stack* stack);
void destroy(Stack* stack);
void push(int val, Stack* stack);
void pop(Stack* stack);
int is_empty(Stack* stack);
int* peek(Stack* stack);

#endif