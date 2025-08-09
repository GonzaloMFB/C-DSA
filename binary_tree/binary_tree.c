#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int* val;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int val) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL){
        fprintf(stderr, "Failed to allocate %lu bytes of memory\n", sizeof(Node));
        return NULL;
    }
    node->val = malloc(sizeof(int));
    if (node->val == NULL){
        free(node);
        fprintf(stderr, "Failed to allocate %lu bytes of memory\n", sizeof(int));
        return NULL;
    }
    *(node->val) = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroy(Node** root) {
    if (root == NULL) {
        fprintf(stderr, "Cannot dereference NULL pointer, exiting.\n");
        return;
    }
    if (*root == NULL) {
        return;
    }
    // Apply recursion (DFS) to clear the tree postorder.
    free((*root)->val);
    destroy(&(*root)->left);
    destroy(&(*root)->right);

    free(*root);
    *root = NULL;
}

int* get_at_path(Node* node, char* path) {
    // Check the current dereferenced value
    if (*path == '\0'){
        // For the case where the string is empty.
        return node->val;
    }
    else if (*path == 'L') {
        if (node->left != NULL) {
            return get_at_path(node->left, path+1);
        }
        else {
            fprintf(stderr, "Invalid path. Node does not exist\n");
            return NULL;
        }
    }
    else if (*path == 'R') {
        if (node->right != NULL) {
            return get_at_path(node->right, path+1);
        }
        else {
            fprintf(stderr, "Invalid path. Node does not exist\n");
            return NULL;
        }
    }
    else {
        fprintf(stderr, "Invalid character in path: %c\n", *path);
        return NULL;
    }

}

void set_at_path(int val, Node* node, char* path) {
    // Check the current dereferenced value
    if (*path == '\0'){
        // First, free the existing memory.
        if (node->val != NULL) {
            *(node->val) = val;
            return;
        }
        else {
            node->val = malloc(sizeof(int));
            if (node->val == NULL){
                fprintf(stderr, "Failed to allocate %lu bytes of memory\n", sizeof(int));
                return;
            }
            *(node->val) = val;
        }
    }
    else if (*path == 'L') {
        if (node->left != NULL) {
            set_at_path(val, node->left, path+1);
        }
        else {
            fprintf(stderr, "Invalid path. Node does not exist\n");
            return;
        }
    }
    else if (*path == 'R') {
        if (node->right != NULL) {
            set_at_path(val, node->right, path+1);
        }
        else {
            fprintf(stderr, "Invalid path. Node does not exist\n");
            return;
        }
    }
    else {
        fprintf(stderr, "Invalid character in path: %c\n", *path);
        return;
    }

}

void preorder_traversal(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("Node val: %d\n", *(node->val));
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

void inorder_traversal(Node* node) {
    // Visit left subtree, then node, then right subtree
    if (node == NULL) {
        return;
    }
    inorder_traversal(node->left);
    printf("Node val: %d\n", *(node->val));
    inorder_traversal(node->right);
}

void postorder_traversal(Node* node) {
    // Visit left subtree, then right subtree, then node,
    if (node == NULL) {
        return;
    }
    postorder_traversal(node->left);
    postorder_traversal(node->right);
    printf("Node val: %d\n", *(node->val));
}

Node* search(int val, Node* node) {
    // KEY INSIGHT: Recursive functions need TWO types of base cases:
    // 1. Failure base case: "nothing to search" -> return NULL
    // 2. Success base case: "found it!" -> return the result
    
    if (node == NULL) {
        return NULL;  // Failure base case
    }
    if (*(node->val) == val) {
        return node;  // Success base case
    }
    
    // CRITICAL LESSON: Handle recursive return values properly!
    // Don't just call the recursive function - CHECK what it returns.
    // A recursive call can return success (non-NULL) or failure (NULL).
    
    if (node->left != NULL) {
        Node* result = search(val, node->left);
        if (result != NULL) {  // Found it in left subtree!
            return result;
        }
        // If we get here, result was NULL (not found), so keep searching
    }
    if (node->right != NULL) {
        Node* result = search(val, node->right);
        if (result != NULL) {  // Found it in right subtree!
            return result;
        }
    }
    
    // IMPORTANT: Every execution path must return something!
    // This handles: "searched everywhere, didn't find it"
    return NULL;
}

int count_nodes(Node* node) {
    // BEAUTIFUL RECURSION PATTERN: Let return values carry information!
    // Instead of using pointers/global state, let recursion naturally
    // "bubble up" the results from deeper calls.
    
    // Base case -> empty subtree has 0 nodes.
    if (node == NULL) {
        return 0;
    }
    
    // INSIGHT: Each subtree contributes its count to the total
    // Current node (1) + left subtree count + right subtree count
    // This is ADDITIVE because we want ALL nodes counted
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int get_height(Node*node) {
    // RECURSIVE PATTERN INSIGHT: Different problems, different operations!
    // - Count nodes: ADD subtree results (want ALL nodes)
    // - Tree height: MAX of subtree results (want LONGEST path)
    // The structure is the same, but the combining operation changes.
    
    // Base case -> empty subtree is height 0.
    if (node == NULL) {
        return 0;
    }
    
    // KEY INSIGHT: Height = longest path from root to leaf
    // We take MAX because we want the longer of the two paths,
    // "discarding excess nodes" as you put it!
    return 1 + max(get_height(node->left), get_height(node->right));
}

Node* bst_insert(int val, Node* node) {
    if (node == NULL) {
        Node* new_node = create_node(val);
        return new_node;
    }
    if (val < *(node->val)) {
        // Slide to the left
        Node* new_node = bst_insert(val, node->left);
        node->left = new_node;
        
    }
    else if (val > *(node->val)) {
        // Slide to the right
        Node* new_node = bst_insert(val, node->right);
        node->right = new_node;

    }
    else {
        // We found a duplicate.
        fprintf(stderr, "ERROR - BST insertion does not allow for duplicate values.\n");
        return NULL;
    }
    return node;
}

Node* binary_search(int val, Node* node) {
    // Base cases
    if (node == NULL) {
        return NULL;
    }
    if (val == *(node->val)) {
        return node;
    }
    // For traversal, apply binary search.
    // Can return straight because unlike regular tree, if a value is not on the
    // left side, it most definitely won't be on the right side (since it's BST).
    else if (val < *(node->val)) {
        return binary_search(val, node->left);
    }
    else {
        return binary_search(val, node->right);
    }

    return NULL;  // We didn't find anything.
}

Node* bst_find_min(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left == NULL) {
        return root;
    }
    return bst_find_min(root->left);
}

Node* bst_find_max(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->right == NULL) {
        return root;
    }
    return bst_find_max(root->right);
}

Node* bst_delete_by_value(int val, Node* node) {
    if (node == NULL) {
        // Value not found
        return NULL;
    }
    if (val < *(node->val)) {
        // left traversal
        node->left = bst_delete_by_value(val, node->left);
    }
    else if (val > *(node->val)) {
        // right
        node->right = bst_delete_by_value(val, node->right);
    }
    else {
        // Found value to delete
        if (node->left == NULL && node->right == NULL) {
            // Leaf node - no children
            free(node->val);
            free(node);
            return NULL;
        }
        if (node->left == NULL) {
            // Has right child only
            Node* child = node->right;
            free(node->val);
            free(node);
            return child;
        }
        if (node->right == NULL) {
            // Has left child only
            Node* child = node->left;
            free(node->val);
            free(node);
            return child;
        }

        // Two children case. Use predecessor to maintain BST structure.
        Node* pred = node->left;
        while(pred->right != NULL) {
            pred = pred->right;
        }
        // Now that we have the predecessor, free old val and copy the new one.
        free(node->val);
        node->val = malloc(sizeof(int)); // make a new ptr since it's dynamic.
        *(node->val) = *(pred->val); // assign its value

        // Now, delete the predecessor.
        // We target node->left so it won't affect the current node and delete that one.
        node->left = bst_delete_by_value(*(pred->val), node->left);
        return node;
    }
}