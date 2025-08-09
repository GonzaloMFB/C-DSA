#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "binary_tree.h"

// Test counter
int tests_run = 0;
int tests_passed = 0;

// Test helper macros
#define TEST_ASSERT(condition, message) \
    do { \
        tests_run++; \
        if (condition) { \
            tests_passed++; \
            printf("PASSED - %s\n", message); \
        } else { \
            printf("FAILED - %s\n", message); \
        } \
    } while(0)

#define TEST_ASSERT_NULL(ptr, message) \
    TEST_ASSERT((ptr) == NULL, message)

#define TEST_ASSERT_NOT_NULL(ptr, message) \
    TEST_ASSERT((ptr) != NULL, message)

#define TEST_ASSERT_EQUAL(expected, actual, message) \
    TEST_ASSERT((expected) == (actual), message)

// Test helper function to create a simple test tree
//       1
//      / \
//     2   3
//    /
//   4
Node* create_test_tree() {
    Node* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    return root;
}

// === MEMORY MANAGEMENT TESTS ===

void test_create_node() {
    printf("\n=== Testing create_node ===\n");
    
    Node* node = create_node(42);
    TEST_ASSERT_NOT_NULL(node, "create_node returns non-NULL");
    TEST_ASSERT_NOT_NULL(node->val, "node->val is allocated");
    TEST_ASSERT_EQUAL(42, *(node->val), "node value is correct");
    TEST_ASSERT_NULL(node->left, "left child is NULL");
    TEST_ASSERT_NULL(node->right, "right child is NULL");
    
    destroy(&node);
    TEST_ASSERT_NULL(node, "destroy sets pointer to NULL");
}

void test_destroy() {
    printf("\n=== Testing destroy ===\n");
    
    Node* tree = create_test_tree();
    TEST_ASSERT_NOT_NULL(tree, "test tree created");
    
    destroy(&tree);
    TEST_ASSERT_NULL(tree, "destroy sets root to NULL");
    
    // Test destroying NULL pointer (should not crash)
    Node* null_tree = NULL;
    destroy(&null_tree);
    TEST_ASSERT_NULL(null_tree, "destroying NULL tree is safe");
}

// === PATH-BASED NAVIGATION TESTS ===

void test_get_at_path() {
    printf("\n=== Testing get_at_path ===\n");
    
    Node* tree = create_test_tree();
    
    // Test root access
    int* val = get_at_path(tree, "");
    TEST_ASSERT_NOT_NULL(val, "get root with empty path");
    TEST_ASSERT_EQUAL(1, *val, "root value correct");
    
    // Test left child
    val = get_at_path(tree, "L");
    TEST_ASSERT_NOT_NULL(val, "get left child");
    TEST_ASSERT_EQUAL(2, *val, "left child value correct");
    
    // Test right child
    val = get_at_path(tree, "R");
    TEST_ASSERT_NOT_NULL(val, "get right child");
    TEST_ASSERT_EQUAL(3, *val, "right child value correct");
    
    // Test left-left path
    val = get_at_path(tree, "LL");
    TEST_ASSERT_NOT_NULL(val, "get left-left child");
    TEST_ASSERT_EQUAL(4, *val, "left-left child value correct");
    
    // Test invalid paths
    val = get_at_path(tree, "LR");
    TEST_ASSERT_NULL(val, "invalid path returns NULL");
    
    val = get_at_path(tree, "X");
    TEST_ASSERT_NULL(val, "invalid character returns NULL");
    
    destroy(&tree);
}

void test_set_at_path() {
    printf("\n=== Testing set_at_path ===\n");
    
    Node* tree = create_test_tree();
    
    // Test setting root value
    set_at_path(99, tree, "");
    int* val = get_at_path(tree, "");
    TEST_ASSERT_EQUAL(99, *val, "set root value");
    
    // Test setting left child
    set_at_path(88, tree, "L");
    val = get_at_path(tree, "L");
    TEST_ASSERT_EQUAL(88, *val, "set left child value");
    
    // Test setting deep path
    set_at_path(77, tree, "LL");
    val = get_at_path(tree, "LL");
    TEST_ASSERT_EQUAL(77, *val, "set left-left child value");
    
    destroy(&tree);
}

// === TREE TRAVERSAL TESTS ===

void test_traversals() {
    printf("\n=== Testing traversals ===\n");
    
    Node* tree = create_test_tree();
    
    printf("Preorder traversal (should be 1, 2, 4, 3):\n");
    preorder_traversal(tree);
    
    printf("Inorder traversal (should be 4, 2, 1, 3):\n");
    inorder_traversal(tree);
    
    printf("Postorder traversal (should be 4, 2, 3, 1):\n");
    postorder_traversal(tree);
    
    TEST_ASSERT(1, "traversals completed without crashing");
    
    destroy(&tree);
}

// === TREE OPERATIONS TESTS ===

void test_search() {
    printf("\n=== Testing search ===\n");
    
    Node* tree = create_test_tree();
    
    // Test finding existing values
    Node* found = search(1, tree);
    TEST_ASSERT_NOT_NULL(found, "search finds root");
    TEST_ASSERT_EQUAL(1, *(found->val), "found correct root value");
    
    found = search(2, tree);
    TEST_ASSERT_NOT_NULL(found, "search finds left child");
    TEST_ASSERT_EQUAL(2, *(found->val), "found correct left value");
    
    found = search(4, tree);
    TEST_ASSERT_NOT_NULL(found, "search finds deep node");
    TEST_ASSERT_EQUAL(4, *(found->val), "found correct deep value");
    
    // Test searching for non-existent value
    found = search(999, tree);
    TEST_ASSERT_NULL(found, "search returns NULL for non-existent value");
    
    // Test searching in NULL tree
    found = search(1, NULL);
    TEST_ASSERT_NULL(found, "search in NULL tree returns NULL");
    
    destroy(&tree);
}

void test_count_nodes() {
    printf("\n=== Testing count_nodes ===\n");
    
    Node* tree = create_test_tree();
    
    int count = count_nodes(tree);
    TEST_ASSERT_EQUAL(4, count, "count_nodes returns correct count");
    
    // Test empty tree
    count = count_nodes(NULL);
    TEST_ASSERT_EQUAL(0, count, "empty tree has 0 nodes");
    
    // Test single node
    Node* single = create_node(42);
    count = count_nodes(single);
    TEST_ASSERT_EQUAL(1, count, "single node tree has 1 node");
    
    destroy(&tree);
    destroy(&single);
}

void test_get_height() {
    printf("\n=== Testing get_height ===\n");
    
    Node* tree = create_test_tree();
    
    int height = get_height(tree);
    TEST_ASSERT_EQUAL(3, height, "test tree height is 3");
    
    // Test empty tree
    height = get_height(NULL);
    TEST_ASSERT_EQUAL(0, height, "empty tree height is 0");
    
    // Test single node
    Node* single = create_node(42);
    height = get_height(single);
    TEST_ASSERT_EQUAL(1, height, "single node height is 1");
    
    destroy(&tree);
    destroy(&single);
}

// === UTILITY TESTS ===

void test_max() {
    printf("\n=== Testing max utility ===\n");
    
    TEST_ASSERT_EQUAL(5, max(3, 5), "max(3, 5) = 5");
    TEST_ASSERT_EQUAL(7, max(7, 2), "max(7, 2) = 7");
    TEST_ASSERT_EQUAL(4, max(4, 4), "max(4, 4) = 4");
    TEST_ASSERT_EQUAL(0, max(-1, 0), "max(-1, 0) = 0");
}

// === BST OPERATION TESTS ===

// Helper function to create a simple BST
//       5
//      / \
//     3   7
//    / \   \
//   1   4   9
Node* create_test_bst() {
    Node* root = NULL;
    root = bst_insert(5, root);
    root = bst_insert(3, root);
    root = bst_insert(7, root);
    root = bst_insert(1, root);
    root = bst_insert(4, root);
    root = bst_insert(9, root);
    return root;
}

void test_bst_insert() {
    printf("\n=== Testing BST Insert ===\n");
    
    Node* root = NULL;
    
    // Test inserting into empty tree
    root = bst_insert(10, root);
    TEST_ASSERT_NOT_NULL(root, "Insert into empty tree creates root");
    TEST_ASSERT_EQUAL(10, *(root->val), "Root value correct");
    
    // Test inserting smaller values (should go left)
    root = bst_insert(5, root);
    TEST_ASSERT_NOT_NULL(root->left, "Smaller value goes left");
    TEST_ASSERT_EQUAL(5, *(root->left->val), "Left child value correct");
    
    // Test inserting larger values (should go right)
    root = bst_insert(15, root);
    TEST_ASSERT_NOT_NULL(root->right, "Larger value goes right");
    TEST_ASSERT_EQUAL(15, *(root->right->val), "Right child value correct");
    
    // Test BST property with inorder traversal
    printf("Inorder traversal (should be sorted): ");
    inorder_traversal(root);
    
    destroy(&root);
}

void test_binary_search() {
    printf("\n=== Testing BST Search ===\n");
    
    Node* bst = create_test_bst();
    
    // Test finding existing values
    Node* found = binary_search(5, bst);
    TEST_ASSERT_NOT_NULL(found, "Find root value");
    TEST_ASSERT_EQUAL(5, *(found->val), "Found correct root value");
    
    found = binary_search(1, bst);
    TEST_ASSERT_NOT_NULL(found, "Find leftmost value");
    TEST_ASSERT_EQUAL(1, *(found->val), "Found correct leftmost value");
    
    found = binary_search(9, bst);
    TEST_ASSERT_NOT_NULL(found, "Find rightmost value");
    TEST_ASSERT_EQUAL(9, *(found->val), "Found correct rightmost value");
    
    // Test searching for non-existent values
    found = binary_search(100, bst);
    TEST_ASSERT_NULL(found, "Search for non-existent large value returns NULL");
    
    found = binary_search(0, bst);
    TEST_ASSERT_NULL(found, "Search for non-existent small value returns NULL");
    
    destroy(&bst);
}

void test_bst_find_min_max() {
    printf("\n=== Testing BST Find Min/Max ===\n");
    
    Node* bst = create_test_bst();
    
    // Test find minimum
    Node* min_node = bst_find_min(bst);
    TEST_ASSERT_NOT_NULL(min_node, "Find minimum in BST");
    TEST_ASSERT_EQUAL(1, *(min_node->val), "Minimum value is correct");
    
    // Test find maximum
    Node* max_node = bst_find_max(bst);
    TEST_ASSERT_NOT_NULL(max_node, "Find maximum in BST");
    TEST_ASSERT_EQUAL(9, *(max_node->val), "Maximum value is correct");
    
    // Test with empty tree
    Node* empty = NULL;
    TEST_ASSERT_NULL(bst_find_min(empty), "Find min in empty tree returns NULL");
    TEST_ASSERT_NULL(bst_find_max(empty), "Find max in empty tree returns NULL");
    
    destroy(&bst);
}

void test_bst_delete() {
    printf("\n=== Testing BST Delete ===\n");
    
    // Test deleting leaf node
    Node* bst = create_test_bst();
    bst = bst_delete_by_value(1, bst);  // Delete leaf
    Node* found = binary_search(1, bst);
    TEST_ASSERT_NULL(found, "Deleted leaf node is gone");
    
    // Verify BST property still holds
    printf("After deleting leaf (1), inorder: ");
    inorder_traversal(bst);
    
    // Test deleting node with one child
    bst = bst_delete_by_value(7, bst);  // Delete node with one child
    found = binary_search(7, bst);
    TEST_ASSERT_NULL(found, "Deleted node with one child is gone");
    found = binary_search(9, bst);  // Its child should still exist
    TEST_ASSERT_NOT_NULL(found, "Child of deleted node still exists");
    
    printf("After deleting node with one child (7), inorder: ");
    inorder_traversal(bst);
    
    // Test deleting node with two children
    bst = bst_delete_by_value(3, bst);  // Delete node with two children
    found = binary_search(3, bst);
    TEST_ASSERT_NULL(found, "Deleted node with two children is gone");
    
    // Both children should still exist
    found = binary_search(4, bst);
    TEST_ASSERT_NOT_NULL(found, "Right child of deleted node still exists");
    
    printf("After deleting node with two children (3), inorder: ");
    inorder_traversal(bst);
    
    // Test deleting root
    bst = bst_delete_by_value(5, bst);
    found = binary_search(5, bst);
    TEST_ASSERT_NULL(found, "Deleted root is gone");
    
    printf("After deleting root (5), inorder: ");
    inorder_traversal(bst);
    
    // Test deleting from empty tree
    Node* empty = NULL;
    empty = bst_delete_by_value(999, empty);
    TEST_ASSERT_NULL(empty, "Deleting from empty tree returns NULL");
    
    destroy(&bst);
}

void test_bst_comprehensive() {
    printf("\n=== Testing BST Comprehensive Operations ===\n");
    
    Node* bst = NULL;
    
    // Build BST with multiple insertions
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int num_values = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < num_values; i++) {
        bst = bst_insert(values[i], bst);
    }
    
    printf("Built BST with values: ");
    for (int i = 0; i < num_values; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    
    printf("Inorder traversal (should be sorted): ");
    inorder_traversal(bst);
    
    // Test all values can be found
    int found_count = 0;
    for (int i = 0; i < num_values; i++) {
        if (binary_search(values[i], bst) != NULL) {
            found_count++;
        }
    }
    TEST_ASSERT_EQUAL(num_values, found_count, "All inserted values can be found");
    
    // Test tree properties
    int node_count = count_nodes(bst);
    TEST_ASSERT_EQUAL(num_values, node_count, "Node count matches insertions");
    
    int height = get_height(bst);
    TEST_ASSERT(height > 0, "Tree has positive height");
    printf("Tree height: %d\n", height);
    
    destroy(&bst);
}

// === MAIN TEST RUNNER ===

int main() {
    printf("Running Binary Tree & BST Tests...\n");
    printf("===================================\n");
    
    // Run binary tree tests
    test_create_node();
    test_destroy();
    test_get_at_path();
    test_set_at_path();
    test_traversals();
    test_search();
    test_count_nodes();
    test_get_height();
    test_max();
    
    // Run BST tests
    test_bst_insert();
    test_binary_search();
    test_bst_find_min_max();
    test_bst_delete();
    test_bst_comprehensive();
    
    // Print summary
    printf("\n===================================\n");
    printf("Test Summary: %d/%d tests passed\n", tests_passed, tests_run);
    
    if (tests_passed == tests_run) {
        printf("🎉 All tests passed!\n");
        return 0;
    } else {
        printf("❌ %d tests failed\n", tests_run - tests_passed);
        return 1;
    }
}