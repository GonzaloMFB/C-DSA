#include <stdio.h>
#include <assert.h>
#include "binary_search.h"

void test_single_element() {
    printf("Testing single element array...\n");
    int arr[] = {5};
    assert(binary_search(5, arr, 1) == 0);
    assert(binary_search(3, arr, 1) == -1);
    printf("SUCCESS - Single element tests passed\n");
}

void test_small_array() {
    printf("Testing small array...\n");
    int arr[] = {1, 3, 5, 7};
    
    // Test finding each element
    assert(binary_search(1, arr, 4) == 0);
    assert(binary_search(3, arr, 4) == 1);
    assert(binary_search(5, arr, 4) == 2);
    assert(binary_search(7, arr, 4) == 3);
    
    // Test non-existent elements
    assert(binary_search(0, arr, 4) == -1);
    assert(binary_search(2, arr, 4) == -1);
    assert(binary_search(4, arr, 4) == -1);
    assert(binary_search(6, arr, 4) == -1);
    assert(binary_search(8, arr, 4) == -1);
    
    printf("SUCCESS - Small array tests passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    int arr[] = {1, 2, 3, 4, 5};
    
    // Test first and last elements
    assert(binary_search(1, arr, 5) == 0);
    assert(binary_search(5, arr, 5) == 4);
    
    // Test empty array
    assert(binary_search(1, NULL, 0) == -1);
    assert(binary_search(1, arr, 0) == -1);
    
    // Test NULL array
    assert(binary_search(1, NULL, 5) == -1);
    
    printf("SUCCESS - Edge case tests passed\n");
}

void test_larger_array() {
    printf("Testing larger array...\n");
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    
    assert(binary_search(2, arr, 10) == 0);
    assert(binary_search(10, arr, 10) == 4);
    assert(binary_search(20, arr, 10) == 9);
    assert(binary_search(1, arr, 10) == -1);
    assert(binary_search(21, arr, 10) == -1);
    assert(binary_search(15, arr, 10) == -1);
    
    printf("SUCCESS - Larger array tests passed\n");
}

void test_recursive_single_element() {
    printf("Testing recursive single element array...\n");
    int arr[] = {5};
    assert(recursive_bin_search(5, arr, 0, 0) == 0);
    assert(recursive_bin_search(3, arr, 0, 0) == -1);
    printf("SUCCESS - Recursive single element tests passed\n");
}

void test_recursive_small_array() {
    printf("Testing recursive small array...\n");
    int arr[] = {1, 3, 5, 7};
    
    // Test finding each element
    assert(recursive_bin_search(1, arr, 0, 3) == 0);
    assert(recursive_bin_search(3, arr, 0, 3) == 1);
    assert(recursive_bin_search(5, arr, 0, 3) == 2);
    assert(recursive_bin_search(7, arr, 0, 3) == 3);
    
    // Test non-existent elements
    assert(recursive_bin_search(0, arr, 0, 3) == -1);
    assert(recursive_bin_search(2, arr, 0, 3) == -1);
    assert(recursive_bin_search(4, arr, 0, 3) == -1);
    assert(recursive_bin_search(6, arr, 0, 3) == -1);
    assert(recursive_bin_search(8, arr, 0, 3) == -1);
    
    printf("SUCCESS - Recursive small array tests passed\n");
}

void test_recursive_edge_cases() {
    printf("Testing recursive edge cases...\n");
    int arr[] = {1, 2, 3, 4, 5};
    
    // Test first and last elements
    assert(recursive_bin_search(1, arr, 0, 4) == 0);
    assert(recursive_bin_search(5, arr, 0, 4) == 4);
    
    // Test invalid range (start > end)
    assert(recursive_bin_search(1, arr, 3, 2) == -1);
    
    // Test NULL array
    assert(recursive_bin_search(1, NULL, 0, 4) == -1);
    
    // Test negative indices
    assert(recursive_bin_search(1, arr, -1, 4) == -1);
    assert(recursive_bin_search(1, arr, 0, -1) == -1);
    
    printf("SUCCESS - Recursive edge case tests passed\n");
}

void test_recursive_larger_array() {
    printf("Testing recursive larger array...\n");
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    
    assert(recursive_bin_search(2, arr, 0, 9) == 0);
    assert(recursive_bin_search(10, arr, 0, 9) == 4);
    assert(recursive_bin_search(20, arr, 0, 9) == 9);
    assert(recursive_bin_search(1, arr, 0, 9) == -1);
    assert(recursive_bin_search(21, arr, 0, 9) == -1);
    assert(recursive_bin_search(15, arr, 0, 9) == -1);
    
    printf("SUCCESS - Recursive larger array tests passed\n");
}

int main() {
    printf("Running binary search tests...\n\n");
    
    printf("=== ITERATIVE TESTS ===\n");
    test_single_element();
    test_small_array();
    test_edge_cases();
    test_larger_array();
    
    printf("\n=== RECURSIVE TESTS ===\n");
    test_recursive_single_element();
    test_recursive_small_array();
    test_recursive_edge_cases();
    test_recursive_larger_array();
    
    printf("\nSUCCESS - All tests passed!\n");
    return 0;
}