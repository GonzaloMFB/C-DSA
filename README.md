# Data Structures and Algorithms in C

A comprehensive collection of fundamental data structures and algorithms implemented in C. This repository serves as a learning resource and reference for computer science students and developers looking to understand core DSA concepts.

## Repository Structure

Each directory contains a complete implementation with:
- **Header file** (`.h`) - Interface definitions and function declarations
- **Source file** (`.c`) - Implementation of the data structure/algorithm
- **Test file** (`test_*.c`) - Unit tests and usage examples
- **README.md** - Detailed explanation of the concept

## Data Structures

| Directory | Data Structure | Description |
|-----------|---------------|-------------|
| [`binary_tree/`](binary_tree/) | Binary Tree | Tree data structure with at most two children per node |
| [`d_linked_list/`](d_linked_list/) | Doubly Linked List | Linear data structure with bidirectional node connections |
| [`dequeue/`](dequeue/) | Double-ended Queue | Queue allowing insertion/deletion at both ends |
| [`heap/`](heap/) | Heap | Complete binary tree maintaining heap property |
| [`hmap/`](hmap/) | Hash Map | Key-value pairs with O(1) average lookup time |
| [`s_linked_list/`](s_linked_list/) | Singly Linked List | Linear data structure with unidirectional node connections |
| [`stack/`](stack/) | Stack | LIFO (Last In, First Out) data structure |
| [`trie/`](trie/) | Trie | Prefix tree for efficient string operations |
| [`vector/`](vector/) | Dynamic Array | Resizable array implementation |

## Algorithms

| Directory | Algorithm | Description |
|-----------|-----------|-------------|
| [`binary_search/`](binary_search/) | Binary Search | Efficient search algorithm for sorted arrays |
| [`dynamic_programming/`](dynamic_programming/) | Dynamic Programming | Problem-solving technique using memoization |
| [`graphs/`](graphs/) | Graph Algorithms | Algorithms for graph traversal and manipulation |
| [`sorting/`](sorting/) | Sorting Algorithms | Various algorithms for ordering data |

## Getting Started

### Prerequisites
- GCC compiler
- Make (optional, for build automation)

### Building and Running

1. Navigate to any directory:
   ```bash
   cd binary_search/
   ```

2. Compile the test program:
   ```bash
   gcc -o test test_binary_search.c binary_search.c
   ```

3. Run the tests:
   ```bash
   ./test
   ```

### Example Usage

```c
#include "vector/vector.h"

int main() {
    Vector* vec = vector_create(10);
    vector_push_back(vec, 42);
    vector_push_back(vec, 84);
    
    printf("Size: %zu\n", vector_size(vec));
    printf("Element 0: %d\n", vector_get(vec, 0));
    
    vector_destroy(vec);
    return 0;
}
```

## Learning Resources

Check the [`notes/`](notes/) directory for additional learning materials:
- **notes.md** - General notes and observations

## Testing

Each implementation includes comprehensive test cases demonstrating:
- Basic operations
- Edge cases
- Performance characteristics
- Memory management

## Contributing

This is a learning repository. Feel free to:
- Suggest improvements
- Add new data structures or algorithms
- Enhance documentation
- Report bugs or issues

## License

This project is for educational purposes. Use freely for learning and reference.

## Learning Goals

- Understand fundamental data structures and their use cases
- Learn algorithm design and analysis
- Practice C programming and memory management
- Develop problem-solving skills