#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
    int max_size;
    int count;
    int* array;
} Vector;

Vector create(int size) {
    Vector vector;
    vector.max_size = size;
    vector.count = 0;
    vector.array = malloc(size * sizeof(int));
    if (vector.array == NULL) {
        fprintf(stderr, "ERROR - Could not malloc %lu bytes.\n", size * sizeof(int));
    }
    return vector;
}

void resize(Vector* vec) {
    int* old_arr = vec->array;
    int old_size = vec->max_size;
    // We duplicate the size.
    // Current count does not change.
    vec->max_size = vec->max_size * 2;
    vec->array = malloc(vec->max_size * sizeof(int));
    if (vec->array == NULL) {
        fprintf(stderr, "ERROR - Could not malloc %lu bytes on resizing.\n", vec->max_size * sizeof(int));
    }
    for (int i = 0; i < old_size; i++) {
        vec->array[i] = old_arr[i];
    }
    free(old_arr);
}

void append(int element, Vector* vec) {
    vec->array[vec->count] = element;
    vec->count += 1;
    // Resize if needed. This is why we do not check if last_idx < max_size
    if (vec->count >= (0.7 * vec->max_size)) {
        resize(vec);
    }
}

void insert(int element, int index, Vector* vec) {
    int last_idx = vec->count - 1;
    if (index < 0) {
        // We're out of bounds
        fprintf(stderr, "Cannot insert at negative index.\n");
    }
    else if (index > last_idx) {
        // We're out of bounds
        fprintf(stderr, "Cannot insert at out-of-bounds index. Use .append instead.\n");
    }
    // Shift all values beyond index to the right.
    // Start from last element to avoid losing any info.
    vec->count++;
    for (int i = vec->count-1; i > index; i--) {
        vec->array[i] = vec->array[i-1];
    }
    vec->array[index] = element;
    // Resize if needed. This is why we do not check if last_idx < max_size
    if (vec->count >= (0.7 * vec->max_size)) {
        resize(vec);
    }
}

void pop(Vector* vec) {
    // NOTE: We do not resize on pop or remove the element.
    // We just lower count to be unable to access it
    vec->count -= 1;
}

int get(int index, Vector* vec) {
    if (index < 0 || index >= vec->count) {
        fprintf(stderr, "Trying to get value at invalid index: %d\n", index);
        return -1;
    }
    return vec->array[index];
}

void set(int index, int element, Vector* vec) {
    if (index < 0 || index >= vec->count) {
        fprintf(stderr, "Trying to get value at invalid index: %d\n", index);
    }
    else {
        vec->array[index] = element;
    }
}

int max_length(Vector* vec) {
    return vec->max_size;
}

int length(Vector* vec) {
    return vec->count;
}

void clear(Vector* vec) {
    vec->count = 0;
    for (int i = 0; i < vec->max_size; i++) {
        vec->array[i] = 0;
    }
}

void destroy(Vector* vec) {
    free(vec->array);
}

