# Binary Tree

A comprehensive binary tree implementation in C providing both general tree operations and Binary Search Tree (BST) functionality. This implementation uses a flexible node structure with pointer-based values and includes path-based navigation.

## Data Structure Overview

A binary tree is a hierarchical data structure where each node has at most two children, referred to as the left and right child. This implementation supports:

- **General Binary Tree**: Basic tree operations and traversals
- **Binary Search Tree (BST)**: Maintains ordering property for efficient searching

## Node Structure

```c
typedef struct Node {
    int* val;           // Pointer to value (allows NULL checking)
    struct Node* left;  // Left child
    struct Node* right; // Right child
} Node;
```

## Time Complexity

### General Tree Operations
- **Search**: O(n) - May need to visit all nodes
- **Traversal**: O(n) - Visit each node once
- **Height Calculation**: O(n) - Visit each node once

### Binary Search Tree Operations
- **Search**: O(log n) average, O(n) worst case
- **Insert**: O(log n) average, O(n) worst case
- **Delete**: O(log n) average, O(n) worst case
- **Find Min/Max**: O(log n) average, O(n) worst case

## Space Complexity
- **Memory**: O(n) for storing n nodes
- **Recursion Stack**: O(h) where h is the height of the tree

## Core Functions

### Memory Management
- `create_node(int val)` - Creates a new tree node
- `destroy(Node** root)` - Recursively destroys entire tree

### Path-Based Navigation
- `get_at_path(Node* node, char* path)` - Gets value at path (e.g., "LR")
- `set_at_path(int val, Node* node, char* path)` - Sets value at path

### Tree Traversal
- `preorder_traversal(Node* node)` - Visit: Node → Left → Right
- `inorder_traversal(Node* node)` - Visit: Left → Node → Right
- `postorder_traversal(Node* node)` - Visit: Left → Right → Node

### Tree Operations
- `search(int val, Node* node)` - DFS search for value
- `count_nodes(Node* node)` - Count total nodes in tree
- `get_height(Node* node)` - Calculate tree height

### Binary Search Tree Operations
- `bst_insert(int val, Node* node)` - Insert maintaining BST property
- `binary_search(int val, Node* node)` - Efficient BST search
- `bst_delete_by_value(int val, Node* node)` - Delete maintaining BST property
- `bst_find_min(Node* root)` - Find minimum value (leftmost)
- `bst_find_max(Node* root)` - Find maximum value (rightmost)

## Usage Examples

### Basic Tree Operations

```c
#include "binary_tree.h"
#include <stdio.h>

int main() {
    // Create a simple tree
    Node* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    
    // Traversals
    printf("Preorder: ");
    preorder_traversal(root);   // Output: 1 2 4 5 3
    printf("\n");
    
    printf("Inorder: ");
    inorder_traversal(root);    // Output: 4 2 5 1 3
    printf("\n");
    
    printf("Postorder: ");
    postorder_traversal(root);  // Output: 4 5 2 3 1
    printf("\n");
    
    // Tree properties
    printf("Node count: %d\n", count_nodes(root));
    printf("Height: %d\n", get_height(root));
    
    // Path-based access
    int* val = get_at_path(root, "LL");  // Left then Left = 4
    if (val) printf("Value at path LL: %d\n", *val);
    
    // Clean up
    destroy(&root);
    return 0;
}
```

### Binary Search Tree Operations

```c
#include "binary_tree.h"
#include <stdio.h>

int main() {
    Node* bst_root = NULL;
    
    // Build BST
    bst_root = bst_insert(50, bst_root);
    bst_root = bst_insert(30, bst_root);
    bst_root = bst_insert(70, bst_root);
    bst_root = bst_insert(20, bst_root);
    bst_root = bst_insert(40, bst_root);
    bst_root = bst_insert(60, bst_root);
    bst_root = bst_insert(80, bst_root);
    
    // Search
    Node* found = binary_search(40, bst_root);
    if (found) printf("Found: %d\n", *(found->val));
    
    // Find min/max
    Node* min_node = bst_find_min(bst_root);
    Node* max_node = bst_find_max(bst_root);
    printf("Min: %d, Max: %d\n", *(min_node->val), *(max_node->val));
    
    // Inorder traversal of BST gives sorted order
    printf("Sorted order: ");
    inorder_traversal(bst_root);  // Output: 20 30 40 50 60 70 80
    printf("\n");
    
    // Delete node
    bst_root = bst_delete_by_value(30, bst_root);
    
    destroy(&bst_root);
    return 0;
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_binary_tree test_binary_tree.c binary_tree.c
```

Run the tests:
```bash
./test_binary_tree
```

## Applications

### General Binary Trees
- Expression trees for mathematical expressions
- Decision trees for algorithms
- Huffman coding trees
- File system hierarchies

### Binary Search Trees
- Implementing associative arrays/maps
- Database indexing
- Priority queues
- Symbol tables in compilers

## Tree Traversal Types

1. **Preorder (NLR)**: Process node before children
   - Use case: Creating a copy of the tree, prefix expressions
   
2. **Inorder (LNR)**: Process left, node, then right
   - Use case: Getting sorted sequence from BST
   
3. **Postorder (LRN)**: Process children before node
   - Use case: Deleting tree, calculating directory sizes

## BST Properties

- **Left Subtree**: All values less than parent
- **Right Subtree**: All values greater than parent
- **Inorder Traversal**: Produces sorted sequence
- **Balanced BST**: Height is O(log n), ensuring efficient operations

## Memory Management

- All nodes are dynamically allocated
- Use `destroy()` to free entire tree
- Path-based operations return pointers to existing values
- Proper NULL checking prevents segmentation faults