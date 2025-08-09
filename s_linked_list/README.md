# Singly Linked List

A singly linked list is a linear data structure where each node contains data and a pointer to the next node in the sequence. This implementation provides fundamental linked list operations with dynamic memory management.

## Data Structure Overview

A singly linked list consists of nodes connected in a single direction:
- **Sequential Access**: Elements accessed by traversing from head
- **Dynamic Size**: Can grow and shrink during runtime
- **Memory Efficient**: Only allocates memory for actual elements
- **Unidirectional**: Can only traverse forward through the list

## Node Structure

```c
typedef struct Node {
    int val;           // Data value stored in the node
    struct Node* next; // Pointer to the next node (NULL for last node)
} Node;
```

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Access/Search | O(n) | Must traverse from head to find element |
| Insertion at head | O(1) | Direct operation with head pointer |
| Insertion at tail | O(n) | Must traverse to end |
| Insertion at index | O(n) | Must traverse to position |
| Deletion at head | O(1) | Direct operation with head pointer |
| Deletion at index | O(n) | Must traverse to find predecessor |
| Length calculation | O(n) | Must count all nodes |

## Space Complexity
- **Memory per node**: O(1) - Each node stores value + 1 pointer
- **Total memory**: O(n) - Linear with number of elements

## Core Functions

### Memory Management
- `create_node(int val)` - Creates a new node with given value
- `destroy(Node* list)` - Recursively frees all nodes in the list

### Basic Operations
- `length(Node* list)` - Returns the number of nodes in the list
- `get_at(int index, Node* list)` - Gets value at specified index
- `find_value(int target, Node* list)` - Returns pointer to node containing target value

### Insertion Operations
- `prepend(int val, Node** list)` - Adds element at the beginning
- `append(int val, Node* list)` - Adds element at the end
- `insert_at_index(int index, int val, Node** list)` - Inserts at specific position

### Deletion Operations
- `remove_at_index(int index, Node** list)` - Removes element at specific position

## Usage Examples

### Basic List Operations

```c
#include "s_linked_list.h"
#include <stdio.h>

int main() {
    // Create initial node (head of list)
    Node* head = create_node(10);
    
    // Add elements
    prepend(5, &head);    // List: [5, 10]
    append(20, head);     // List: [5, 10, 20]
    append(30, head);     // List: [5, 10, 20, 30]
    
    // Insert at specific position
    insert_at_index(2, 15, &head);  // List: [5, 10, 15, 20, 30]
    
    printf("List length: %d\n", length(head));  // Output: 5
    
    // Access elements
    printf("Element at index 0: %d\n", get_at(0, head));  // Output: 5
    printf("Element at index 2: %d\n", get_at(2, head));  // Output: 15
    
    // Find specific value
    Node* found = find_value(20, head);
    if (found) {
        printf("Found value 20 in the list\n");
    }
    
    // Remove element
    remove_at_index(1, &head);  // List: [5, 15, 20, 30]
    printf("Length after removal: %d\n", length(head));  // Output: 4
    
    // Clean up memory
    destroy(head);
    return 0;
}
```

### List Traversal

```c
void print_list(Node* head) {
    printf("List: ");
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

void print_list_recursive(Node* head) {
    if (head == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", head->val);
    print_list_recursive(head->next);
}
```

### Advanced Operations

```c
// Reverse the linked list
Node* reverse_list(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;   // Store next
        current->next = prev;   // Reverse current link
        prev = current;         // Move prev forward
        current = next;         // Move current forward
    }
    
    return prev;  // New head
}

// Remove duplicates from sorted list
Node* remove_duplicates_sorted(Node* head) {
    Node* current = head;
    
    while (current != NULL && current->next != NULL) {
        if (current->val == current->next->val) {
            Node* duplicate = current->next;
            current->next = current->next->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
    
    return head;
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_s_linked_list test_s_linked_list.c s_linked_list.c
```

Run the tests:
```bash
./test_s_linked_list
```

## Advantages

1. **Dynamic Size**: Can grow and shrink during runtime
2. **Memory Efficient**: Only allocates memory for stored elements
3. **Insertion/Deletion**: Efficient at the beginning (O(1))
4. **Simple Implementation**: Straightforward pointer manipulation
5. **Memory Locality**: Good for sequential access patterns

## Disadvantages

1. **No Random Access**: Cannot directly access element at arbitrary index
2. **Sequential Access**: Must traverse from head to reach elements
3. **Extra Memory**: Requires storage for next pointers
4. **Cache Performance**: Nodes may not be contiguous in memory
5. **No Backward Traversal**: Cannot move backwards through the list

## Applications

Singly linked lists are commonly used in:

### System Programming
- **Memory Management**: Free lists in memory allocators
- **Process Lists**: Operating system task management
- **Undo Operations**: Simple undo stack implementation
- **Function Call Stack**: Alternative to array-based stacks

### Data Structure Implementation
- **Stack Implementation**: LIFO operations using head insertion/deletion
- **Queue Implementation**: Insertion at tail, deletion at head
- **Graph Adjacency Lists**: Representing graph connections
- **Hash Table Chaining**: Collision resolution in hash maps

### Algorithm Applications
- **Polynomial Representation**: Coefficients and exponents
- **Sparse Matrix**: Store only non-zero elements
- **Music Playlist**: Sequential song playback
- **Browser History**: Page navigation (with additional features)

## Comparison with Arrays

| Feature | Singly Linked List | Array |
|---------|-------------------|-------|
| Access Time | O(n) | O(1) |
| Search Time | O(n) | O(n) |
| Insert at Beginning | O(1) | O(n) |
| Insert at End | O(n) | O(1) amortized |
| Insert at Index | O(n) | O(n) |
| Delete at Beginning | O(1) | O(n) |
| Memory Usage | Higher (pointers) | Lower (contiguous) |
| Cache Performance | Poor | Excellent |
| Dynamic Sizing | Yes | No (fixed size) |

## Memory Management Notes

- Always update head pointer when modifying the first node
- Use double pointers (`Node**`) for functions that modify the head
- Check for NULL pointers before dereferencing
- Free memory using `destroy()` to prevent memory leaks
- Handle edge cases: empty list, single element list
- Ensure proper linking when inserting/deleting nodes

## Common Pitfalls

1. **Memory Leaks**: Forgetting to free removed nodes
2. **Dangling Pointers**: Accessing freed memory
3. **Lost References**: Not updating head pointer properly
4. **Infinite Loops**: Circular references in the list
5. **Null Pointer Dereference**: Not checking for NULL before access