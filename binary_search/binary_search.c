#include <stdlib.h>
#include <stdio.h>

int binary_search(int val, int* array, int arr_len) {
    if (array == NULL) {
        fprintf(stderr, "ERROR - Cannot pass NULL as array");
        return -1;
    }
    if (arr_len == 0) {
        printf("Target array is empty");
        return -1;
    }
    // Returns the index of the element
    int start = 0;
    int end = arr_len-1;
    int mid;
    while (start <= end) {
        mid = start + (end - start)/2; // 'divide' the array in 2 parts.
        if (array[mid] < val) {
            // Value is bigger; take the right side.
            start = mid + 1;
            continue;
        }
        else if (array[mid] > val) {
            // Value is smaller; take the left side.
            end = mid - 1;
            continue;
        }
        else {
            // Found value.
            return mid;
        }
    }
    // Not found.
    return -1;
}

int recursive_bin_search(int val, int* array, int start, int end) {
    // Assume the user is passing in-bound param for end
    if (array == NULL) {
        fprintf(stderr, "ERROR - Cannot pass NULL as array");
        return -1;
    }
    if (start < 0 || end < 0) {
        fprintf(stderr, "ERROR - Start and end indexes must be >= 0");
        return -1;
    }
    // start > end is the not found condition in binary search.
    if (end >= start) {
        int mid = start + (end - start)/2;
        // Recursion
        if (array[mid] < val) {
            return recursive_bin_search(val, array, mid + 1, end);
        }
        else if (array[mid] > val){
            return recursive_bin_search(val, array, start, mid-1);
        }
        else {
            // Base case - Found.
            return mid;
        }
    }
    return -1;
    
}

