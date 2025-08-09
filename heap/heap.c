#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int count;  // for current count
    int length; // to know our max length
    int* array; // vector to resize.
} Heap;

Heap* create_heap(int size) {
    Heap* heap = malloc(sizeof(Heap));
    if (heap == NULL) {
        fprintf(stderr, "ERROR - Could not malloc %lu bytes.\n", sizeof(Heap));
    }
    heap->count = 0;
    heap->length = size;
    heap->array = malloc(size * sizeof(int));
    if (heap->array == NULL) {
        free(heap);
        fprintf(stderr, "ERROR - Could not malloc %lu bytes.\n", size * sizeof(int));
    }
    return heap;
}

void resize(Heap* heap) {
    heap->length = heap->length * 2;
    int* tmp = malloc(sizeof(int) * heap->length);
    for (int i = 0; i < heap->count; i ++) {
        tmp[i] = heap->array[i];
    }
    free(heap->array);
    heap->array = tmp;
}

void destroy(Heap** heap){
    // We need to free the array and then free the heap itself.
    free((*heap)->array);
    free(*heap);
    *heap = NULL;
}

int* peek(Heap* heap) {
    // User is responsible for dereferencing.
    if (heap == NULL) {
        // NULL heap, invalid case.
        fprintf(stderr, "ERROR - Must pass a valid Heap*");
        return NULL;
    }
    if (heap->count == 0) {
        // No element, valid case.
        return NULL;
    }
    else {
        return heap->array;
    }
}

void insert(int val, Heap* heap) {
    if (heap == NULL) {
        // NULL heap, invalid case.
        fprintf(stderr, "ERROR - Must pass a valid Heap*");
        return;
    }
    if (heap->count == 0) {
        // No element, just insert at the head.
        // We do int rather than int* so we don't lose addr of the malloc'd array.
        heap->array[0] = val;
        (heap->count)++;
        return;
    }
    // Now, we get to the case where we have more elements.
    // Insert at count (last index +1, works out perfectly)
    int child_idx = heap->count;
    heap->array[child_idx] = val;
    (heap->count)++;
    if (heap->count > 0.7 * heap->length) {
        resize(heap);
    }
    // Heap element inserted at the end, now we have to bubble up.
    int parent_idx = ((child_idx)-1) / 2; // C rounds to 0 on int division.
    int parent_val = heap->array[parent_idx];
    while (val < parent_val) {
        // Parent has to be smaller than children, so swap if val < parent_val
        // Swap parent and child values.
        heap->array[child_idx] = parent_val;
        heap->array[parent_idx] = val;

        // Update parent index and val.
        child_idx = parent_idx;
        if (parent_idx == 0) break; // Reached root
        parent_idx = (parent_idx-1) / 2;
        parent_val = heap->array[parent_idx];
    }
}

int choose_child(Heap* heap, int a, int b) {
    // Get the min of 2 vals.
    if (a >= heap->count && b >= heap->count) {
        // No valid indices found, we're at the end of the heap.
        return -1;
    }
    if (b >= heap->count) {
        // Only a is within bounds
        return a;
    }
    if (a >= heap->count) {
        // Only b is within bounds
        return b;
    }
    return (heap->array[a] < heap->array[b]) ? a : b;
}

int* pop(Heap* heap) {
    // Returns element at the head.
    if (heap == NULL) {
        // Bad case
        fprintf(stderr, "ERROR - Must pass a valid Heap*");
        return NULL;
    }
    if (heap->count == 0) {
        // Valid case, empty heap with no elements.
        return NULL;
    }
    static int popped_value;
    popped_value = heap->array[0];
    // Now, if the count > 1, we have to do some restructuring.
    // Otherwise, return immediately.
    // we do not need to nullify any values.
    // Just decrease count so we can't access the position anymore.
    if (heap->count == 1) {
        (heap->count)--;  
        return &popped_value;
    }
    // Else, we do some restructuring.

    // Move the last element to the top.
    // Deletion of the last copy will be done via count decrement.
    heap->array[0] = heap->array[heap->count-1];
    (heap->count)--;
    int parent_idx = 0;
    int parent_val = heap->array[parent_idx];
    int child_idx = choose_child(heap, (2* parent_idx +1), (2* parent_idx +2));
    if (child_idx == -1) {
        // Edge case for a heap with original size 2 (e.g. [1,2])
        // We pop 1, 2 remains. No valid children to iterate to.
        return &popped_value;
    }
    int child_val = heap->array[child_idx];
    while (parent_val >= child_val && child_idx != -1) {
        // Parent has to be smaller than children.
        // Swap the values.
        heap->array[child_idx] = parent_val;
        heap->array[parent_idx] = child_val;

        // Now recreate the indices.
        parent_idx = child_idx;
        parent_val = heap->array[parent_idx];
        child_idx = choose_child(heap, (2* child_idx +1), (2* child_idx +2));
        if (child_idx != -1) {
            child_val = heap->array[child_idx];
        }
    }
    
    return &popped_value;
    
}
