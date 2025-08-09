# Deque (Double-Ended Queue)

A deque (pronounced "deck") is a double-ended queue that allows insertion and deletion of elements at both the front and back ends. This implementation uses a circular array with dynamic resizing to provide efficient operations at both ends.

## Data Structure Overview

The deque combines the benefits of both stacks and queues:
- **Stack-like**: Push/pop operations at one end
- **Queue-like**: FIFO operations using front and back
- **Double-ended**: Operations at both front and back ends

This implementation uses a circular array approach with automatic resizing when capacity is reached.

## Deque Structure

```c
typedef struct Deque {
    int count;       // Number of elements currently in deque
    int front_idx;   // Index of front element
    int back_idx;    // Index of back element  
    int max_length;  // Current capacity of the array
    int* array;      // Dynamic array storing elements
} Deque;
```

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Push Front | O(1) amortized | Add element to front |
| Push Back | O(1) amortized | Add element to back |
| Pop Front | O(1) | Remove element from front |
| Pop Back | O(1) | Remove element from back |
| Access Front | O(1) | Get front element |
| Access Back | O(1) | Get back element |
| Resize | O(n) | Only when capacity exceeded |

## Space Complexity
- **Memory**: O(n) where n is the maximum capacity
- **Dynamic Resizing**: Grows automatically when needed

## Core Functions

### Memory Management
- `create_deque(int size)` - Creates a new deque with initial capacity
- `destroy(Deque* deque)` - Frees memory and destroys the deque
- `resize(Deque* deque)` - Doubles the capacity when full

### Operations
- `push_front(int val, Deque* deque)` - Adds element to the front
- `push_back(int val, Deque* deque)` - Adds element to the back
- `pop_front(Deque* deque)` - Removes element from the front
- `pop_back(Deque* deque)` - Removes element from the back

## Usage Examples

### Basic Deque Operations

```c
#include "deque.h"
#include <stdio.h>

int main() {
    // Create deque with initial capacity of 4
    Deque* dq = create_deque(4);
    
    // Add elements to both ends
    push_back(10, dq);   // Deque: [10]
    push_back(20, dq);   // Deque: [10, 20]
    push_front(5, dq);   // Deque: [5, 10, 20]
    push_front(1, dq);   // Deque: [1, 5, 10, 20]
    
    printf("Count: %d\n", dq->count);  // Output: 4
    
    // Remove from both ends
    pop_front(dq);       // Deque: [5, 10, 20]
    pop_back(dq);        // Deque: [5, 10]
    
    printf("Count after pops: %d\n", dq->count);  // Output: 2
    
    // Clean up
    destroy(dq);
    return 0;
}
```

### Using Deque as Different Data Structures

```c
// Use as Stack (LIFO) - push/pop from same end
void stack_example(Deque* dq) {
    push_back(1, dq);
    push_back(2, dq);
    push_back(3, dq);
    
    pop_back(dq);  // Remove 3
    pop_back(dq);  // Remove 2
    // Stack behavior: last in, first out
}

// Use as Queue (FIFO) - push to back, pop from front
void queue_example(Deque* dq) {
    push_back(1, dq);
    push_back(2, dq);
    push_back(3, dq);
    
    pop_front(dq);  // Remove 1
    pop_front(dq);  // Remove 2
    // Queue behavior: first in, first out
}

// Use as Double-ended queue
void deque_example(Deque* dq) {
    push_front(1, dq);  // Add to front
    push_back(2, dq);   // Add to back
    pop_front(dq);      // Remove from front
    pop_back(dq);       // Remove from back
    // Full flexibility at both ends
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_deque test_deque.c deque.c
```

Run the tests:
```bash
./test_deque
```

## Circular Array Implementation

The deque uses a circular array approach where:
- `front_idx` points to the first element
- `back_idx` points to the position after the last element
- Indices wrap around using modulo arithmetic
- Automatic resizing when capacity is exceeded

### Index Calculation
```c
// Front insertion: front_idx = (front_idx - 1 + max_length) % max_length
// Back insertion: back_idx = (back_idx + 1) % max_length  
// Front removal: front_idx = (front_idx + 1) % max_length
// Back removal: back_idx = (back_idx - 1 + max_length) % max_length
```

## Advantages

1. **Constant Time Operations**: O(1) insertion/deletion at both ends
2. **Memory Efficient**: Circular array minimizes memory usage
3. **Versatile**: Can be used as stack, queue, or deque
4. **Dynamic Sizing**: Automatically grows when needed
5. **Cache Friendly**: Array-based implementation has good locality

## Disadvantages

1. **No Random Access**: Cannot access middle elements efficiently
2. **Resizing Overhead**: Occasional O(n) operation when growing
3. **Complex Index Management**: Circular array logic can be error-prone
4. **Memory Overhead**: May have unused capacity

## Applications

Deques are commonly used in:

- **Sliding Window Problems**: Maintain elements in a window efficiently
- **Palindrome Checking**: Add characters from both ends
- **Undo/Redo Operations**: Support operations at both ends
- **Work Stealing**: Task scheduling in parallel processing
- **Browser History**: Navigate forward and backward
- **A-Star Algorithm**: Frontier management in pathfinding
- **Job Scheduling**: Priority task management

## Implementation Details

### Dynamic Resizing
- When deque becomes full, capacity is doubled
- All elements are copied to new array in proper order
- Old array is freed to prevent memory leaks

### Edge Cases Handled
- Empty deque operations
- Single element operations
- Wrapping around array boundaries
- Memory allocation failures

## Comparison with Other Data Structures

| Feature | Array | Linked List | Deque |
|---------|--------|-------------|-------|
| Front Insert | O(n) | O(1) | O(1) |
| Back Insert | O(1) | O(1) | O(1) |
| Front Delete | O(n) | O(1) | O(1) |
| Back Delete | O(1) | O(n) | O(1) |
| Random Access | O(1) | O(n) | O(n) |
| Memory | Continuous | Fragmented | Continuous |

The deque provides the best of both worlds for operations at the ends while maintaining reasonable memory efficiency.