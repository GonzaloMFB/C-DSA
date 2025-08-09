#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/**
 * Binary Tree Library
 * A general-purpose binary tree implementation with path-based navigation
 * and comprehensive tree operations.
 */

/**
 * Node structure for binary tree
 * Uses int* for values to allow NULL returns without ambiguity
 */
typedef struct Node {
    int* val;           // Pointer to value (allows NULL checking)
    struct Node* left;  // Left child
    struct Node* right; // Right child
} Node;

// === MEMORY MANAGEMENT ===

/**
 * Creates a new tree node with given value
 * @param val: Integer value to store
 * @return: Pointer to new node, or NULL if allocation fails
 */
Node* create_node(int val);

/**
 * Recursively destroys entire tree (postorder)
 * @param root: Pointer to root pointer (allows setting to NULL)
 */
void destroy(Node** root);

// === PATH-BASED NAVIGATION ===

/**
 * Gets value at specified path (e.g., "LR" = left then right)
 * @param node: Starting node
 * @param path: String of 'L' and 'R' characters
 * @return: Pointer to value, or NULL if path invalid
 */
int* get_at_path(Node* node, char* path);

/**
 * Sets value at specified path
 * @param val: New value to set
 * @param node: Starting node
 * @param path: String of 'L' and 'R' characters
 */
void set_at_path(int val, Node* node, char* path);

// === TREE TRAVERSAL ===

/**
 * Preorder traversal: Visit node, then left, then right
 * @param node: Starting node
 */
void preorder_traversal(Node* node);

/**
 * Inorder traversal: Visit left, then node, then right
 * Produces sorted order for BSTs
 * @param node: Starting node
 */
void inorder_traversal(Node* node);

/**
 * Postorder traversal: Visit left, then right, then node
 * Useful for safe deletion and bottom-up operations
 * @param node: Starting node
 */
void postorder_traversal(Node* node);

// === TREE OPERATIONS ===

/**
 * Searches for a value in the tree (DFS)
 * @param val: Value to search for
 * @param node: Starting node
 * @return: Pointer to node containing value, or NULL if not found
 */
Node* search(int val, Node* node);

/**
 * Counts total number of nodes in tree
 * @param node: Starting node
 * @return: Number of nodes in subtree
 */
int count_nodes(Node* node);

/**
 * Calculates height of tree (longest path from root to leaf)
 * @param node: Starting node
 * @return: Height of subtree (0 for empty tree)
 */
int get_height(Node* node);

// === BINARY SEARCH TREE (BST) OPERATIONS ===

/**
 * Inserts a value into BST maintaining order property
 * @param val: Value to insert
 * @param node: Root of BST
 * @return: Root of BST after insertion
 */
Node* bst_insert(int val, Node* node);

/**
 * Searches for a value in BST using binary search (O(log n))
 * @param val: Value to search for
 * @param node: Root of BST
 * @return: Pointer to node containing value, or NULL if not found
 */
Node* binary_search(int val, Node* node);

/**
 * Deletes a value from BST maintaining order property
 * Handles all three cases: leaf, one child, two children
 * @param val: Value to delete
 * @param node: Root of BST
 * @return: Root of BST after deletion
 */
Node* bst_delete_by_value(int val, Node* node);

/**
 * Finds minimum value in BST (leftmost node)
 * @param root: Root of BST
 * @return: Pointer to node with minimum value, or NULL if empty
 */
Node* bst_find_min(Node* root);

/**
 * Finds maximum value in BST (rightmost node)
 * @param root: Root of BST
 * @return: Pointer to node with maximum value, or NULL if empty
 */
Node* bst_find_max(Node* root);

// === UTILITY FUNCTIONS ===

/**
 * Returns maximum of two integers
 * @param a: First integer
 * @param b: Second integer
 * @return: The larger value
 */
int max(int a, int b);

#endif