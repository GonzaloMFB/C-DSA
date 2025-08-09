# Heap (Binary Heap)

A heap is a specialized tree-based data structure that satisfies the heap property. This implementation provides a min-heap where the parent node is always smaller than or equal to its children. It uses an array-based representation for efficient storage and automatic resizing.

## Data Structure Overview

A binary heap is a complete binary tree that maintains the heap property:
- **Min-Heap**: Parent ≤ Children (root contains minimum element)
- **Complete Binary Tree**: All levels filled except possibly the last, filled left to right
- **Array Representation**: Efficient storage using indices for parent-child relationships

## Heap Structure

```c
typedef struct Heap {
    int count;   // Current number of elements
    int length;  // Maximum capacity
    int* array;  // Dynamic array storing elements
} Heap;
```

## Array Index Relationships

For any element at index `i`:
- **Parent**: `(i - 1) / 2`
- **Left Child**: `2 * i + 1`
- **Right Child**: `2 * i + 2`

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Insert | O(log n) | Add element and bubble up |
| Pop (Extract Min) | O(log n) | Remove root and bubble down |
| Peek | O(1) | View minimum element |
| Build Heap | O(n) | Create heap from array |
| Resize | O(n) | Double capacity when full |

## Space Complexity
- **Memory**: O(n) for storing n elements
- **Auxiliary Space**: O(1) for operations (excluding recursion stack)

## Core Functions

### Memory Management
- `create_heap(int size)` - Creates heap with initial capacity
- `destroy(Heap** heap)` - Frees memory and sets pointer to NULL

### Heap Operations
- `peek(Heap* heap)` - Returns pointer to minimum element (NULL if empty)
- `insert(int val, Heap* heap)` - Adds element maintaining heap property
- `pop(Heap* heap)` - Removes and returns minimum element (NULL if empty)

### Internal Functions
- `resize(Heap* heap)` - Doubles capacity when needed
- `choose_child(Heap* heap, int a, int b)` - Helper for bubble-down operation

## Usage Examples

### Basic Heap Operations

```c
#include "heap.h"
#include <stdio.h>

int main() {
    // Create heap with initial capacity of 10
    Heap* heap = create_heap(10);
    
    // Insert elements
    insert(50, heap);
    insert(30, heap);
    insert(70, heap);
    insert(20, heap);
    insert(40, heap);
    insert(60, heap);
    insert(80, heap);
    
    printf("Heap size: %d\n", heap->count);  // Output: 7
    
    // Peek at minimum
    int* min = peek(heap);
    if (min) {
        printf("Minimum element: %d\n", *min);  // Output: 20
    }
    
    // Extract elements in sorted order
    printf("Elements in ascending order: ");
    while (heap->count > 0) {
        int* val = pop(heap);
        if (val) {
            printf("%d ", *val);
        }
    }
    printf("\n");  // Output: 20 30 40 50 60 70 80
    
    // Clean up
    destroy(&heap);
    return 0;
}
```

### Priority Queue Implementation

```c
typedef struct Task {
    int priority;
    char* description;
} Task;

// Use heap for task scheduling (lower number = higher priority)
void priority_queue_example() {
    Heap* pq = create_heap(5);
    
    // Add tasks with different priorities
    insert(3, pq);  // Low priority task
    insert(1, pq);  // High priority task  
    insert(2, pq);  // Medium priority task
    insert(1, pq);  // Another high priority task
    
    // Process tasks in priority order
    while (pq->count > 0) {
        int* priority = pop(pq);
        if (priority) {
            printf("Processing task with priority: %d\n", *priority);
        }
    }
    // Output: 1, 1, 2, 3 (highest to lowest priority)
    
    destroy(&pq);
}
```

### Heap Sort Algorithm

```c
void heap_sort(int arr[], int n) {
    Heap* heap = create_heap(n);
    
    // Insert all elements into heap
    for (int i = 0; i < n; i++) {
        insert(arr[i], heap);
    }
    
    // Extract elements back to array (sorted order)
    for (int i = 0; i < n; i++) {
        int* min = pop(heap);
        if (min) {
            arr[i] = *min;
        }
    }
    
    destroy(&heap);
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_heap test_heap.c heap.c
```

Run the tests:
```bash
./test_heap
```

## Heap Operations Details

### Insert Operation
1. Add new element at the end of array
2. "Bubble up": Compare with parent and swap if necessary
3. Repeat until heap property is satisfied
4. Resize array if capacity exceeded

### Pop (Extract Min) Operation
1. Store root element (minimum) to return
2. Move last element to root position
3. Decrease count
4. "Bubble down": Compare with children and swap with smaller child
5. Repeat until heap property is satisfied

### Dynamic Resizing
- When heap becomes full, capacity is doubled
- All elements are copied to new larger array
- Old array is freed to prevent memory leaks

## Heap Types

### Min-Heap (This Implementation)
- Root contains smallest element
- Used for: Priority queues, shortest path algorithms
- Parent ≤ Children

### Max-Heap
- Root contains largest element
- Used for: Heap sort (descending), maximum priority queues
- Parent ≥ Children

## Applications

Heaps are commonly used in:

### Algorithm Implementation
- **Heap Sort**: O(n log n) sorting algorithm
- **Dijkstra's Algorithm**: Shortest path finding
- **Prim's Algorithm**: Minimum spanning tree
- **Huffman Coding**: Data compression

### System Design
- **Priority Queues**: Task scheduling, process management
- **Event Simulation**: Discrete event simulation
- **Memory Management**: Garbage collection algorithms
- **Real-time Systems**: Deadline scheduling

## Advantages

1. **Efficient Priority Operations**: O(log n) insert/extract
2. **Space Efficient**: Array-based representation
3. **Guaranteed Access**: Always know minimum/maximum element
4. **Cache Friendly**: Array storage provides good locality
5. **Dynamic**: Automatic resizing handles any input size

## Disadvantages

1. **No Random Access**: Cannot efficiently access arbitrary elements
2. **No Search**: Finding specific value requires O(n) time
3. **Not Sorted**: Only partial ordering (root is min/max)
4. **Memory Overhead**: May have unused capacity after resizing

## Comparison with Other Data Structures

| Feature | Heap | Binary Search Tree | Sorted Array |
|---------|------|-------------------|--------------|
| Insert | O(log n) | O(log n) average | O(n) |
| Find Min | O(1) | O(log n) | O(1) |
| Delete Min | O(log n) | O(log n) | O(n) |
| Space | O(n) | O(n) | O(n) |
| Memory Layout | Contiguous | Fragmented | Contiguous |

## Heap Property Maintenance

The heap implementation ensures:
- **Structural Property**: Complete binary tree maintained
- **Ordering Property**: Min-heap property preserved
- **Dynamic Resizing**: Automatic capacity management
- **Memory Safety**: Proper bounds checking and NULL pointer handling