#ifndef HEAP_H
#define HEAP_H

typedef struct Heap {
    int count;  // for current count
    int length; // to know our max length
    int* array; // vector to resize.
} Heap;

// Create a new heap with initial capacity
Heap* create_heap(int size);

// Destroy heap and free all memory
void destroy(Heap** heap);

// Peek at the minimum element (returns pointer, NULL if empty)
int* peek(Heap* heap);

// Insert an element into the heap
void insert(int val, Heap* heap);

// Remove and return the minimum element (returns pointer, NULL if empty)
int* pop(Heap* heap);

// Internal function to resize the heap when needed
void resize(Heap* heap);

// Internal helper function to choose the smaller child
int choose_child(Heap* heap, int a, int b);

#endif