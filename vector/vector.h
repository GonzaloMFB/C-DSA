#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    int max_size;
    int count;
    int* array;
} Vector;

// Creates vector.
Vector create(int size);

// Adds element at the end of the array.
void append(int element, Vector* vec);

// Inserts element at index.
void insert(int element, int index, Vector* vec);

// Removes last element.
void pop(Vector* vec);

// Gets value at particular index.
int get(int index, Vector* vec);

// Sets value at particular index.
void set(int index, int element, Vector* vec);

// Resets vector to zero.
void clear(Vector* vec);

// Destroys vector struct.
void destroy(Vector* vec);

// Returns max size of vector.
int max_length(Vector* vec);

// Returns current size of vector.
int length(Vector* vec);

#endif

