#include "d_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_create_node() {
    printf("Testing create_node...\n");
    
    Node* node = create_node(42);
    assert(node != NULL);
    assert(node->val == 42);
    assert(node->next == NULL);
    assert(node->prev == NULL);
    
    free(node);
    printf("SUCCESS - create_node tests passed\n");
}

void test_length() {
    printf("Testing length...\n");
    
    // Test empty list
    Node* head = NULL;
    assert(length(head) == 0);
    
    // Test single node
    head = create_node(1);
    assert(length(head) == 1);
    
    // Test multiple nodes
    Node* second = create_node(2);
    Node* third = create_node(3);
    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;
    
    assert(length(head) == 3);
    
    // Cleanup
    free(head);
    free(second);
    free(third);
    
    printf("SUCCESS - length tests passed\n");
}

void test_get() {
    printf("Testing get...\n");
    
    // Create a small list: 1 <-> 2 <-> 3
    Node* head = create_node(1);
    Node* second = create_node(2);
    Node* third = create_node(3);
    
    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;
    
    // Test valid indices
    assert(get(0, head) == 1);
    assert(get(1, head) == 2);
    assert(get(2, head) == 3);
    
    // Test invalid indices (should return -1)
    assert(get(-1, head) == -1);
    assert(get(3, head) == -1);
    
    // Test empty list
    assert(get(0, NULL) == -1);
    
    // Cleanup
    free(head);
    free(second);
    free(third);
    
    printf("SUCCESS - get tests passed\n");
}

void test_set() {
    printf("Testing set...\n");
    
    // Create a small list: 1 <-> 2 <-> 3
    Node* head = create_node(1);
    Node* second = create_node(2);
    Node* third = create_node(3);
    
    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;
    
    // Test setting values
    set(10, 0, head);
    assert(get(0, head) == 10);
    
    set(20, 1, head);
    assert(get(1, head) == 20);
    
    set(30, 2, head);
    assert(get(2, head) == 30);
    
    // Test invalid indices (should not crash)
    set(99, -1, head);
    set(99, 3, head);
    
    // Cleanup
    free(head);
    free(second);
    free(third);
    
    printf("SUCCESS - set tests passed\n");
}

void test_prepend() {
    printf("Testing prepend...\n");
    
    // Test prepending to empty list
    Node* head = NULL;
    prepend(1, &head);
    assert(head != NULL);
    assert(head->val == 1);
    assert(head->next == NULL);
    assert(head->prev == NULL);
    assert(length(head) == 1);
    
    // Test prepending to non-empty list
    prepend(2, &head);
    assert(head->val == 2);
    assert(head->next->val == 1);
    assert(head->prev == NULL);
    assert(head->next->prev == head);
    assert(length(head) == 2);
    
    prepend(3, &head);
    assert(head->val == 3);
    assert(head->next->val == 2);
    assert(head->next->next->val == 1);
    assert(length(head) == 3);
    
    // Cleanup
    destroy(&head);
    
    printf("SUCCESS - prepend tests passed\n");
}

void test_append() {
    printf("Testing append...\n");
    
    // Create initial node
    Node* head = create_node(1);
    
    // Test appending to single node
    append(2, head);
    assert(length(head) == 2);
    assert(get(0, head) == 1);
    assert(get(1, head) == 2);
    assert(head->next->prev == head);
    assert(head->next->next == NULL);
    
    // Test appending more nodes
    append(3, head);
    append(4, head);
    assert(length(head) == 4);
    assert(get(0, head) == 1);
    assert(get(1, head) == 2);
    assert(get(2, head) == 3);
    assert(get(3, head) == 4);
    
    // Verify bidirectional links
    Node* current = head;
    while (current->next != NULL) {
        assert(current->next->prev == current);
        current = current->next;
    }
    
    // Cleanup
    Node* temp_head = head;
    destroy(&temp_head);
    
    printf("SUCCESS - append tests passed\n");
}

void test_remove_at_index() {
    printf("Testing remove_at_index...\n");
    
    // Create list: 1 <-> 2 <-> 3 <-> 4
    Node* head = create_node(1);
    append(2, head);
    append(3, head);
    append(4, head);
    
    // Test removing middle element
    remove_at_index(2, &head); // Remove 3
    assert(length(head) == 3);
    assert(get(0, head) == 1);
    assert(get(1, head) == 2);
    assert(get(2, head) == 4);
    
    // Test removing head
    remove_at_index(0, &head); // Remove 1
    assert(length(head) == 2);
    assert(get(0, head) == 2);
    assert(get(1, head) == 4);
    assert(head->prev == NULL);
    
    // Test removing last element
    remove_at_index(1, &head); // Remove 4
    assert(length(head) == 1);
    assert(get(0, head) == 2);
    
    // Test removing only element
    remove_at_index(0, &head); // Remove 2
    assert(head == NULL);
    
    printf("SUCCESS - remove_at_index tests passed\n");
}

void test_insert_at_index() {
    printf("Testing insert_at_index...\n");
    
    // Create list: 1 <-> 3
    Node* head = create_node(1);
    append(3, head);
    
    // Test inserting in middle
    insert_at_index(1, 2, &head); // Insert 2 at index 1
    assert(length(head) == 3);
    assert(get(0, head) == 1);
    assert(get(1, head) == 2);
    assert(get(2, head) == 3);
    
    // Test inserting at beginning
    insert_at_index(0, 0, &head); // Insert 0 at index 0
    assert(length(head) == 4);
    assert(get(0, head) == 0);
    assert(get(1, head) == 1);
    assert(head->prev == NULL);
    
    // Test inserting at end (index == length)
    insert_at_index(4, 4, &head); // Insert 4 at end
    assert(length(head) == 5);
    assert(get(4, head) == 4);
    
    // Verify bidirectional links
    Node* current = head;
    while (current->next != NULL) {
        assert(current->next->prev == current);
        current = current->next;
    }
    
    // Test inserting into empty list
    Node* empty_head = NULL;
    insert_at_index(0, 100, &empty_head);
    assert(empty_head != NULL);
    assert(get(0, empty_head) == 100);
    assert(length(empty_head) == 1);
    
    // Cleanup
    destroy(&head);
    destroy(&empty_head);
    
    printf("SUCCESS - insert_at_index tests passed\n");
}

void test_destroy() {
    printf("Testing destroy...\n");
    
    // Create a list
    Node* head = create_node(1);
    append(2, head);
    append(3, head);
    append(4, head);
    
    assert(length(head) == 4);
    
    // Destroy the list
    destroy(&head);
    assert(head == NULL);
    
    printf("SUCCESS - destroy tests passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Test operations on empty list
    Node* head = NULL;
    assert(length(head) == 0);
    assert(get(0, head) == -1);
    
    // Test single node operations
    head = create_node(42);
    assert(length(head) == 1);
    assert(get(0, head) == 42);
    
    set(100, 0, head);
    assert(get(0, head) == 100);
    
    // Test removing only node
    remove_at_index(0, &head);
    assert(head == NULL);
    
    printf("SUCCESS - edge cases tests passed\n");
}

void test_bidirectional_links() {
    printf("Testing bidirectional links integrity...\n");
    
    Node* head = create_node(1);
    append(2, head);
    append(3, head);
    append(4, head);
    
    // Test forward traversal
    Node* current = head;
    int expected_forward[] = {1, 2, 3, 4};
    int i = 0;
    while (current != NULL) {
        assert(current->val == expected_forward[i]);
        current = current->next;
        i++;
    }
    
    // Test backward traversal
    current = head;
    while (current->next != NULL) {
        current = current->next; // Go to last node
    }
    
    int expected_backward[] = {4, 3, 2, 1};
    i = 0;
    while (current != NULL) {
        assert(current->val == expected_backward[i]);
        current = current->prev;
        i++;
    }
    
    destroy(&head);
    printf("SUCCESS - bidirectional links tests passed\n");
}

int main() {
    printf("Running doubly linked list tests...\n\n");
    
    test_create_node();
    test_length();
    test_get();
    test_set();
    test_prepend();
    test_append();
    test_remove_at_index();
    test_insert_at_index();
    test_destroy();
    test_edge_cases();
    test_bidirectional_links();
    
    printf("\nSUCCESS - All doubly linked list tests passed!\n");
    return 0;
}