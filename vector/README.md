# Vector (Dynamic Array)

A vector is a dynamic array that can grow and shrink in size during runtime. This implementation provides an array-like interface with automatic memory management, allowing efficient random access while handling capacity expansion transparently.

## Data Structure Overview

A vector combines the benefits of arrays with dynamic sizing:
- **Random Access**: Direct access to elements by index in O(1) time
- **Dynamic Sizing**: Automatically grows when more space is needed
- **Contiguous Memory**: Elements stored sequentially for cache efficiency
- **Array Interface**: Familiar indexing and iteration patterns

## Vector Structure

```c
typedef struct Vector {
    int max_size;   // Current capacity of the vector
    int count;      // Number of elements currently stored
    int* array;     // Dynamic array storing the elements
} Vector;
```

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Access (get/set) | O(1) | Direct index-based access |
| Append | O(1) amortized | Add element at end |
| Insert at index | O(n) | Shift elements after insertion point |
| Pop (remove last) | O(1) | Remove last element |
| Search | O(n) | Linear search through elements |
| Clear | O(1) | Reset count (elements remain allocated) |

## Space Complexity
- **Memory**: O(n) where n is the capacity
- **Growth Strategy**: Typically doubles capacity when full
- **Unused Space**: May have unused allocated capacity

## Core Functions

### Vector Management
- `create(int size)` - Creates vector with initial capacity
- `destroy(Vector* vec)` - Frees memory used by vector
- `clear(Vector* vec)` - Resets vector to empty (keeps allocation)

### Element Operations
- `append(int element, Vector* vec)` - Adds element at the end
- `insert(int element, int index, Vector* vec)` - Inserts at specific index
- `pop(Vector* vec)` - Removes last element
- `get(int index, Vector* vec)` - Returns element at index
- `set(int index, int element, Vector* vec)` - Updates element at index

### Utility Functions
- `length(Vector* vec)` - Returns number of elements
- `max_length(Vector* vec)` - Returns current capacity

## Usage Examples

### Basic Vector Operations

```c
#include "vector.h"
#include <stdio.h>

int main() {
    // Create vector with initial capacity of 5
    Vector vec = create(5);
    
    // Add elements to the end
    append(10, &vec);
    append(20, &vec);
    append(30, &vec);
    append(40, &vec);
    append(50, &vec);
    
    printf("Vector length: %d\n", length(&vec));           // Output: 5
    printf("Vector capacity: %d\n", max_length(&vec));     // Output: 5
    
    // Add one more element (will trigger resize)
    append(60, &vec);
    printf("After resize - capacity: %d\n", max_length(&vec)); // Output: 10 (or similar)
    
    // Access elements
    for (int i = 0; i < length(&vec); i++) {
        printf("Element %d: %d\n", i, get(i, &vec));
    }
    
    // Modify elements
    set(2, 35, &vec);  // Change third element to 35
    printf("Modified element 2: %d\n", get(2, &vec));  // Output: 35
    
    // Remove last element
    pop(&vec);
    printf("After pop - length: %d\n", length(&vec));  // Output: 5
    
    // Clean up
    destroy(&vec);
    return 0;
}
```

### Dynamic Array Example

```c
void dynamic_example() {
    Vector numbers = create(2);  // Start small to demonstrate growth
    
    // Fill with numbers 1 to 20
    for (int i = 1; i <= 20; i++) {
        append(i, &numbers);
        printf("Added %d, capacity: %d, count: %d\n", 
               i, max_length(&numbers), length(&numbers));
    }
    
    // Vector automatically grew as needed
    // Typical growth: 2 -> 4 -> 8 -> 16 -> 32
    
    destroy(&numbers);
}
```

### Insert and Shift Operations

```c
void insert_example() {
    Vector vec = create(10);
    
    // Build initial array: [10, 20, 30, 40, 50]
    for (int i = 1; i <= 5; i++) {
        append(i * 10, &vec);
    }
    
    printf("Original: ");
    for (int i = 0; i < length(&vec); i++) {
        printf("%d ", get(i, &vec));
    }
    printf("\n");  // Output: 10 20 30 40 50
    
    // Insert 25 at index 2
    insert(25, 2, &vec);  // Shifts elements right
    
    printf("After insert: ");
    for (int i = 0; i < length(&vec); i++) {
        printf("%d ", get(i, &vec));
    }
    printf("\n");  // Output: 10 20 25 30 40 50
    
    destroy(&vec);
}
```

### Vector as a Buffer

```c
typedef struct Buffer {
    Vector data;
    int read_pos;
} Buffer;

Buffer* create_buffer(int initial_capacity) {
    Buffer* buffer = malloc(sizeof(Buffer));
    buffer->data = create(initial_capacity);
    buffer->read_pos = 0;
    return buffer;
}

void write_to_buffer(Buffer* buffer, int value) {
    append(value, &buffer->data);
}

int read_from_buffer(Buffer* buffer) {
    if (buffer->read_pos < length(&buffer->data)) {
        return get(buffer->read_pos++, &buffer->data);
    }
    return -1;  // No more data
}

int buffer_available(Buffer* buffer) {
    return length(&buffer->data) - buffer->read_pos;
}
```

### Algorithms with Vectors

```c
// Binary search on sorted vector
int binary_search_vector(Vector* vec, int target) {
    int left = 0;
    int right = length(vec) - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int mid_val = get(mid, vec);
        
        if (mid_val == target) {
            return mid;
        } else if (mid_val < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;  // Not found
}

// Remove duplicates from sorted vector
void remove_duplicates(Vector* vec) {
    if (length(vec) <= 1) return;
    
    int write_pos = 1;
    for (int read_pos = 1; read_pos < length(vec); read_pos++) {
        if (get(read_pos, vec) != get(read_pos - 1, vec)) {
            set(write_pos++, get(read_pos, vec), vec);
        }
    }
    // Update count to reflect new size
    vec->count = write_pos;
}

// Find maximum element
int find_max(Vector* vec) {
    if (length(vec) == 0) return INT_MIN;
    
    int max_val = get(0, vec);
    for (int i = 1; i < length(vec); i++) {
        int current = get(i, vec);
        if (current > max_val) {
            max_val = current;
        }
    }
    return max_val;
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_vector test_vector.c vector.c
```

Run the tests:
```bash
./test_vector
```

## Dynamic Resizing

The vector automatically grows when capacity is exceeded:

### Growth Strategy
1. **Initial Capacity**: Set during creation
2. **Growth Trigger**: When append() is called on full vector
3. **Growth Factor**: Typically doubles the current capacity
4. **Memory Management**: Old array is copied to new larger array

### Amortized Analysis
- **Individual Operations**: Some inserts are O(n) due to resizing
- **Amortized Cost**: O(1) per operation over many operations
- **Total Cost**: N inserts cost O(N) total, making average cost O(1)

## Applications

Vectors are versatile and used in many scenarios:

### System Programming
- **Buffer Management**: I/O buffers, network packets
- **Dynamic Arrays**: When size is unknown at compile time
- **Implementation Base**: Foundation for other data structures
- **Memory Pools**: Efficient allocation for similar-sized objects

### Algorithm Implementation
- **Sorting**: Store elements for various sorting algorithms
- **Graph Representation**: Adjacency lists for vertices
- **Dynamic Programming**: Store intermediate results
- **Sliding Window**: Maintain elements in a window

### Application Development
- **Collection Classes**: Store collections of objects
- **Undo/Redo Systems**: Maintain history of operations
- **Game Development**: Store entities, particles, game objects
- **Data Processing**: Accumulate results, batch processing

## Advantages

1. **Random Access**: O(1) access to any element by index
2. **Cache Friendly**: Contiguous memory layout improves performance
3. **Dynamic Sizing**: Grows automatically as needed
4. **Memory Efficient**: Only allocates space for stored elements (plus capacity)
5. **Simple Interface**: Array-like operations are intuitive

## Disadvantages

1. **Insertion Cost**: Inserting in middle requires shifting O(n) elements
2. **Memory Overhead**: May have unused allocated capacity
3. **Reallocation Cost**: Growing requires copying all elements
4. **Fixed Type**: This implementation only stores integers

## Comparison with Other Data Structures

| Feature | Vector | Linked List | Fixed Array | Stack |
|---------|---------|-------------|-------------|-------|
| Random Access | O(1) | O(n) | O(1) | O(n) |
| Insert at End | O(1) avg | O(1) | N/A | O(1) |
| Insert at Middle | O(n) | O(1) if have pointer | N/A | N/A |
| Memory Layout | Contiguous | Fragmented | Contiguous | Contiguous |
| Dynamic Size | Yes | Yes | No | Yes |
| Cache Performance | Excellent | Poor | Excellent | Excellent |

## Memory Management

### Capacity vs Count
- **Capacity (`max_size`)**: Total allocated space
- **Count**: Number of elements currently stored
- **Unused Space**: Capacity - Count

### Growth Patterns
```c
// Typical growth sequence for vector starting at size 2:
// Capacity: 2 -> 4 -> 8 -> 16 -> 32 -> 64 ...
// Insertions: 1-2 -> 3-4 -> 5-8 -> 9-16 -> 17-32 -> 33-64 ...
```

### Memory Considerations
- Use `clear()` to reset without deallocating
- Use `destroy()` to free all memory
- Vector may hold more capacity than needed after many operations
- Consider shrinking strategy for memory-critical applications

## Performance Tips

1. **Pre-allocate**: Create vector with expected final size if known
2. **Batch Operations**: Group insertions to minimize resizing
3. **Avoid Middle Insertion**: Insert at end when possible
4. **Cache Locality**: Sequential access patterns are fastest
5. **Memory Monitoring**: Be aware of capacity vs count for memory usage