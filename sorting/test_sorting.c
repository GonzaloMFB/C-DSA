#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sorting.h"

void print_array(int* array, int count) {
    printf("[");
    for (int i = 0; i < count; i++) {
        printf("%d", array[i]);
        if (i < count - 1) printf(", ");
    }
    printf("]\n");
}

int arrays_equal(int* arr1, int* arr2, int count) {
    for (int i = 0; i < count; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }
    return 1;
}

void test_bubble_sort_basic() {
    int array[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};
    int count = 5;
    
    printf("Before sorting: ");
    print_array(array, count);
    
    bubble_sort(array, count);
    
    printf("After sorting:  ");
    print_array(array, count);
    
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_bubble_sort_basic passed\n");
}

void test_bubble_sort_already_sorted() {
    int array[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    bubble_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_bubble_sort_already_sorted passed\n");
}

void test_bubble_sort_reverse_sorted() {
    int array[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    bubble_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_bubble_sort_reverse_sorted passed\n");
}

void test_bubble_sort_duplicates() {
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int expected[] = {1, 1, 2, 3, 4, 5, 5, 6, 9};
    int count = 9;
    
    bubble_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_bubble_sort_duplicates passed\n");
}

void test_bubble_sort_single_element() {
    int array[] = {42};
    int expected[] = {42};
    int count = 1;
    
    bubble_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_bubble_sort_single_element passed\n");
}

void test_bubble_sort_two_elements() {
    int array[] = {2, 1};
    int expected[] = {1, 2};
    int count = 2;
    
    bubble_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_bubble_sort_two_elements passed\n");
}

void test_bubble_sort_negative_numbers() {
    int array[] = {-3, 1, -4, 1, 5, -9, 2};
    int expected[] = {-9, -4, -3, 1, 1, 2, 5};
    int count = 7;
    
    bubble_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_bubble_sort_negative_numbers passed\n");
}

// Selection sort tests
void test_selection_sort_basic() {
    int array[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};
    int count = 5;
    
    selection_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_selection_sort_basic passed\n");
}

void test_selection_sort_already_sorted() {
    int array[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    selection_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_selection_sort_already_sorted passed\n");
}

void test_selection_sort_reverse_sorted() {
    int array[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    selection_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_selection_sort_reverse_sorted passed\n");
}

// Insertion sort tests
void test_insertion_sort_basic() {
    int array[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};
    int count = 5;
    
    insertion_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_insertion_sort_basic passed\n");
}

void test_insertion_sort_already_sorted() {
    int array[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    insertion_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_insertion_sort_already_sorted passed\n");
}

void test_insertion_sort_reverse_sorted() {
    int array[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    insertion_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_insertion_sort_reverse_sorted passed\n");
}

// Quick sort tests
void test_quick_sort_basic() {
    int array[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};
    int count = 5;
    
    quick_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_quick_sort_basic passed\n");
}

void test_quick_sort_already_sorted() {
    int array[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    quick_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_quick_sort_already_sorted passed\n");
}

void test_quick_sort_reverse_sorted() {
    int array[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    quick_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_quick_sort_reverse_sorted passed\n");
}

void test_quick_sort_single_element() {
    int array[] = {42};
    int expected[] = {42};
    int count = 1;
    
    quick_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_quick_sort_single_element passed\n");
}

void test_quick_sort_duplicates() {
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int expected[] = {1, 1, 2, 3, 4, 5, 5, 6, 9};
    int count = 9;
    
    quick_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_quick_sort_duplicates passed\n");
}

void test_quick_sort_two_elements() {
    int array[] = {2, 1};
    int expected[] = {1, 2};
    int count = 2;
    
    quick_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_quick_sort_two_elements passed\n");
}

void test_quick_sort_negative_numbers() {
    int array[] = {-3, 1, -4, 1, 5, -9, 2};
    int expected[] = {-9, -4, -3, 1, 1, 2, 5};
    int count = 7;
    
    quick_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_quick_sort_negative_numbers passed\n");
}

// Merge sort tests
void test_merge_sort_basic() {
    int array[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};
    int count = 5;
    
    merge_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_merge_sort_basic passed\n");
}

void test_merge_sort_already_sorted() {
    int array[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    merge_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_merge_sort_already_sorted passed\n");
}

void test_merge_sort_reverse_sorted() {
    int array[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int count = 5;
    
    merge_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_merge_sort_reverse_sorted passed\n");
}

void test_merge_sort_single_element() {
    int array[] = {42};
    int expected[] = {42};
    int count = 1;
    
    merge_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_merge_sort_single_element passed\n");
}

void test_merge_sort_duplicates() {
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int expected[] = {1, 1, 2, 3, 4, 5, 5, 6, 9};
    int count = 9;
    
    merge_sort(array, count);
    assert(arrays_equal(array, expected, count));
    printf("SUCCESS - test_merge_sort_duplicates passed\n");
}

int main() {
    printf("Running sorting algorithm tests...\n\n");
    
    printf("=== Bubble Sort Tests ===\n");
    test_bubble_sort_basic();
    test_bubble_sort_already_sorted();
    test_bubble_sort_reverse_sorted();
    test_bubble_sort_duplicates();
    test_bubble_sort_single_element();
    test_bubble_sort_two_elements();
    test_bubble_sort_negative_numbers();
    
    printf("\n=== Selection Sort Tests ===\n");
    test_selection_sort_basic();
    test_selection_sort_already_sorted();
    test_selection_sort_reverse_sorted();
    
    printf("\n=== Insertion Sort Tests ===\n");
    test_insertion_sort_basic();
    test_insertion_sort_already_sorted();
    test_insertion_sort_reverse_sorted();
    
    printf("\n=== Quick Sort Tests ===\n");
    test_quick_sort_basic();
    test_quick_sort_already_sorted();
    test_quick_sort_reverse_sorted();
    test_quick_sort_single_element();
    test_quick_sort_duplicates();
    test_quick_sort_two_elements();
    test_quick_sort_negative_numbers();
    
    printf("\n=== Merge Sort Tests ===\n");
    test_merge_sort_basic();
    test_merge_sort_already_sorted();
    test_merge_sort_reverse_sorted();
    test_merge_sort_single_element();
    test_merge_sort_duplicates();
    
    printf("\nSUCCESS - All sorting tests passed!\n");
    return 0;
}