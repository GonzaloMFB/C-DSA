#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test counter
int tests_run = 0;
int tests_passed = 0;

// Test helper macros
#define TEST_ASSERT(condition, message) \
    do { \
        tests_run++; \
        if (condition) { \
            tests_passed++; \
            printf("✓ PASSED - %s\n", message); \
        } else { \
            printf("✗ FAILED - %s\n", message); \
        } \
    } while(0)

#define TEST_ASSERT_NULL(ptr, message) \
    TEST_ASSERT((ptr) == NULL, message)

#define TEST_ASSERT_NOT_NULL(ptr, message) \
    TEST_ASSERT((ptr) != NULL, message)

#define TEST_ASSERT_EQUAL(expected, actual, message) \
    TEST_ASSERT((expected) == (actual), message)

// Helper to verify heap property is maintained
int verify_heap_property(Heap* heap) {
    for (int i = 0; i < heap->count; i++) {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        
        if (left_child < heap->count && heap->array[i] > heap->array[left_child]) {
            return 0; // Heap property violated
        }
        if (right_child < heap->count && heap->array[i] > heap->array[right_child]) {
            return 0; // Heap property violated
        }
    }
    return 1; // Heap property maintained
}

// Helper to print heap state for debugging
void print_heap(Heap* heap, const char* label) {
    printf("%s: [", label);
    for (int i = 0; i < heap->count; i++) {
        printf("%d", heap->array[i]);
        if (i < heap->count - 1) printf(", ");
    }
    printf("] (count: %d, length: %d)\n", heap->count, heap->length);
}

// Test helper function to create a simple test heap
Heap* create_test_heap() {
    //       1
    //      / \
    //     2   3
    //    /
    //   4
    Heap* heap = create_heap(8);
    insert(1, heap);
    insert(2, heap);
    insert(3, heap);
    insert(4, heap);
    return heap;
}

void test_create_heap() {
    printf("\n=== Testing create_heap ===\n");
    
    // Test normal creation
    Heap* heap = create_heap(8);
    TEST_ASSERT_NOT_NULL(heap, "create_heap returns non-NULL");
    TEST_ASSERT_NOT_NULL(heap->array, "heap->array is allocated");
    TEST_ASSERT_EQUAL(0, heap->count, "New heap is empty");
    TEST_ASSERT_EQUAL(8, heap->length, "New heap has correct length");
    destroy(&heap);
    
    // Test small heap creation
    Heap* small_heap = create_heap(1);
    TEST_ASSERT_NOT_NULL(small_heap, "Small heap creation works");
    TEST_ASSERT_EQUAL(1, small_heap->length, "Small heap has correct length");
    destroy(&small_heap);
}

void test_peek() {
    printf("\n=== Testing peek ===\n");
    
    // Test peek on empty heap
    Heap* empty_heap = create_heap(4);
    TEST_ASSERT_NULL(peek(empty_heap), "Peek on empty heap returns NULL");
    destroy(&empty_heap);
    
    // Test peek on populated heap
    Heap* heap = create_test_heap();
    int* val = peek(heap);
    TEST_ASSERT_NOT_NULL(val, "Peek returns non-NULL on populated heap");
    TEST_ASSERT_EQUAL(1, *val, "Peek returns minimum value");
    TEST_ASSERT_EQUAL(4, heap->count, "Peek doesn't modify heap size");
    destroy(&heap);
    
    // Test peek on single element heap
    Heap* single_heap = create_heap(4);
    insert(42, single_heap);
    int* single_val = peek(single_heap);
    TEST_ASSERT_EQUAL(42, *single_val, "Peek works on single element heap");
    destroy(&single_heap);
}

void test_insert() {
    printf("\n=== Testing insert ===\n");
    
    // Test insert into empty heap
    Heap* heap = create_heap(8);
    insert(5, heap);
    TEST_ASSERT_EQUAL(1, heap->count, "Insert into empty heap increases count");
    TEST_ASSERT_EQUAL(5, heap->array[0], "Insert into empty heap places element at root");
    
    // Test multiple insertions maintain heap property
    insert(3, heap);
    insert(7, heap);
    insert(1, heap);
    insert(9, heap);
    TEST_ASSERT_EQUAL(5, heap->count, "Multiple insertions update count correctly");
    TEST_ASSERT(verify_heap_property(heap), "Heap property maintained after multiple insertions");
    TEST_ASSERT_EQUAL(1, heap->array[0], "Minimum element bubbles to root");
    
    destroy(&heap);
    
    // Test insertion sequence that triggers bubble-up
    Heap* bubble_heap = create_heap(8);
    insert(10, bubble_heap);
    insert(5, bubble_heap);
    insert(3, bubble_heap);
    insert(1, bubble_heap); // Should bubble all the way to root
    TEST_ASSERT_EQUAL(1, bubble_heap->array[0], "Element bubbles up to root correctly");
    TEST_ASSERT(verify_heap_property(bubble_heap), "Heap property maintained during bubble-up");
    
    destroy(&bubble_heap);
}

void test_pop() {
    printf("\n=== Testing pop ===\n");
    
    // Test pop on empty heap
    Heap* empty_heap = create_heap(4);
    TEST_ASSERT_NULL(pop(empty_heap), "Pop on empty heap returns NULL");
    destroy(&empty_heap);
    
    // Test pop on single element heap
    Heap* single_heap = create_heap(4);
    insert(42, single_heap);
    int* single_val = pop(single_heap);
    TEST_ASSERT_EQUAL(42, *single_val, "Pop returns correct value from single element heap");
    TEST_ASSERT_EQUAL(0, single_heap->count, "Single element heap becomes empty after pop");
    destroy(&single_heap);
    
    // Test pop on multi-element heap
    Heap* heap = create_test_heap();
    int original_count = heap->count;
    int* val = pop(heap);
    TEST_ASSERT_EQUAL(1, *val, "Pop returns minimum value");
    TEST_ASSERT_EQUAL(original_count - 1, heap->count, "Pop decreases count");
    TEST_ASSERT(verify_heap_property(heap), "Heap property maintained after pop");
    
    // Test consecutive pops return values in ascending order
    int prev_val = *val;
    while (heap->count > 0) {
        int* next_val = pop(heap);
        TEST_ASSERT(prev_val <= *next_val, "Consecutive pops return ascending values");
        prev_val = *next_val;
    }
    
    destroy(&heap);
}

void test_heap_sort() {
    printf("\n=== Testing heap sort behavior ===\n");
    
    // Insert values in random order and verify they come out sorted
    Heap* heap = create_heap(16);
    int values[] = {15, 3, 9, 1, 12, 7, 4, 8, 2, 11};
    int n = sizeof(values) / sizeof(values[0]);
    
    // Insert all values
    for (int i = 0; i < n; i++) {
        insert(values[i], heap);
    }
    
    TEST_ASSERT_EQUAL(n, heap->count, "All values inserted successfully");
    TEST_ASSERT(verify_heap_property(heap), "Heap property maintained after bulk insertion");
    
    // Pop all values and verify they come out sorted
    int prev = 0;
    for (int i = 0; i < n; i++) {
        int* val = pop(heap);
        TEST_ASSERT_NOT_NULL(val, "Pop returns valid value");
        if (i > 0) {
            TEST_ASSERT(prev <= *val, "Values come out in sorted order");
        }
        prev = *val;
    }
    
    destroy(&heap);
}

void test_resize() {
    printf("\n=== Testing resize functionality ===\n");
    
    // Create small heap and force resize
    Heap* heap = create_heap(2);
    int original_length = heap->length;
    
    // Insert enough elements to trigger resize (> 0.7 * capacity)
    insert(1, heap);
    insert(2, heap);
    insert(3, heap); // Should trigger resize
    
    TEST_ASSERT(heap->length > original_length, "Heap length increased after resize");
    TEST_ASSERT_EQUAL(3, heap->count, "All elements preserved after resize");
    TEST_ASSERT(verify_heap_property(heap), "Heap property maintained after resize");
    TEST_ASSERT_EQUAL(1, heap->array[0], "Minimum element still at root after resize");
    
    destroy(&heap);
}

void test_edge_cases() {
    printf("\n=== Testing edge cases ===\n");
    
    // Test duplicate values
    Heap* dup_heap = create_heap(8);
    insert(5, dup_heap);
    insert(5, dup_heap);
    insert(5, dup_heap);
    TEST_ASSERT_EQUAL(3, dup_heap->count, "Duplicate values handled correctly");
    TEST_ASSERT(verify_heap_property(dup_heap), "Heap property maintained with duplicates");
    
    int* val1 = pop(dup_heap);
    int* val2 = pop(dup_heap);
    int* val3 = pop(dup_heap);
    TEST_ASSERT_EQUAL(5, *val1, "First duplicate popped correctly");
    TEST_ASSERT_EQUAL(5, *val2, "Second duplicate popped correctly");
    TEST_ASSERT_EQUAL(5, *val3, "Third duplicate popped correctly");
    
    destroy(&dup_heap);
    
    // Test alternating insert/pop operations
    Heap* alt_heap = create_heap(8);
    insert(10, alt_heap);
    insert(5, alt_heap);
    int* pop1 = pop(alt_heap);
    insert(3, alt_heap);
    insert(8, alt_heap);
    int* pop2 = pop(alt_heap);
    
    TEST_ASSERT_EQUAL(5, *pop1, "First pop in alternating sequence correct");
    TEST_ASSERT_EQUAL(3, *pop2, "Second pop in alternating sequence correct");
    TEST_ASSERT(verify_heap_property(alt_heap), "Heap property maintained during alternating operations");
    
    destroy(&alt_heap);
}

void test_stress() {
    printf("\n=== Stress testing ===\n");
    
    // Large number of operations
    Heap* stress_heap = create_heap(4); // Start small to test resizing
    int num_ops = 1000;
    
    // Insert many elements
    for (int i = num_ops; i > 0; i--) {
        insert(i, stress_heap);
    }
    
    TEST_ASSERT_EQUAL(num_ops, stress_heap->count, "Stress test: all elements inserted");
    TEST_ASSERT(verify_heap_property(stress_heap), "Stress test: heap property maintained");
    TEST_ASSERT_EQUAL(1, stress_heap->array[0], "Stress test: minimum element at root");
    
    // Pop all elements and verify order
    for (int i = 1; i <= num_ops; i++) {
        int* val = pop(stress_heap);
        TEST_ASSERT_EQUAL(i, *val, "Stress test: elements pop in correct order");
    }
    
    TEST_ASSERT_EQUAL(0, stress_heap->count, "Stress test: heap empty after all pops");
    
    destroy(&stress_heap);
}

void test_destroy() {
    printf("\n=== Testing destroy ===\n");
    
    Heap* heap = create_test_heap();
    TEST_ASSERT_NOT_NULL(heap, "Heap created successfully before destroy");
    
    destroy(&heap);
    TEST_ASSERT_NULL(heap, "Heap pointer set to NULL after destroy");
}

void print_test_summary() {
    printf("\n==================================================\n");
    printf("TEST SUMMARY\n");
    printf("==================================================\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);
    printf("Success rate: %.1f%%\n", (float)tests_passed / tests_run * 100);
    
    if (tests_passed == tests_run) {
        printf("\n🎉 ALL TESTS PASSED! Your heap implementation is solid!\n");
    } else {
        printf("\n❌ Some tests failed. Check the output above for details.\n");
    }
}

int main() {
    printf("COMPREHENSIVE HEAP TEST SUITE\n");
    printf("=============================\n");
    
    test_create_heap();
    test_peek();
    test_insert();
    test_pop();
    test_heap_sort();
    test_resize();
    test_edge_cases();
    test_stress();
    test_destroy();
    
    print_test_summary();
    
    return (tests_passed == tests_run) ? 0 : 1;
}