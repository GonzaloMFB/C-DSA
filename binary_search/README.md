# Binary Search

Binary search is an efficient algorithm for finding an item from a sorted list of items. It works by repeatedly dividing the search interval in half and comparing the target value to the middle element of the interval.

## Algorithm Overview

Binary search operates on the principle of "divide and conquer":
1. Compare the target value to the middle element of the array
2. If they match, the search is successful
3. If the target is less than the middle element, search the left half
4. If the target is greater than the middle element, search the right half
5. Repeat until the target is found or the search space is empty

## Time Complexity
- **Best Case**: O(1) - Target is at the middle position
- **Average Case**: O(log n) - Target requires logarithmic divisions
- **Worst Case**: O(log n) - Target is at the end or doesn't exist

## Space Complexity
- **Iterative Implementation**: O(1) - Constant space
- **Recursive Implementation**: O(log n) - Due to call stack

## Implementation

This directory contains two implementations:

### Functions
- `binary_search(int val, int* array, int arr_len)` - Iterative implementation
- `recursive_bin_search(int val, int* array, int start, int end)` - Recursive implementation

### Parameters
- `val` - The target value to search for
- `array` - Pointer to the sorted array
- `arr_len` - Length of the array (iterative version)
- `start` - Starting index (recursive version)
- `end` - Ending index (recursive version)

### Return Value
- Returns the index of the target value if found
- Returns -1 if the target value is not in the array

## Usage Example

```c
#include "binary_search.h"
#include <stdio.h>

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    
    // Iterative approach
    int result = binary_search(target, arr, n);
    if (result != -1)
        printf("Element %d found at index %d\n", target, result);
    else
        printf("Element %d not found\n", target);
    
    // Recursive approach
    int result_rec = recursive_bin_search(target, arr, 0, n - 1);
    if (result_rec != -1)
        printf("Element %d found at index %d\n", target, result_rec);
    else
        printf("Element %d not found\n", target);
    
    return 0;
}
```

## Prerequisites

**IMPORTANT**: The array must be sorted in ascending order for binary search to work correctly.

## Building and Testing

Compile the test program:
```bash
gcc -o test_binary_search test_binary_search.c binary_search.c
```

Run the tests:
```bash
./test_binary_search
```

## Applications

Binary search is commonly used in:
- Searching in sorted databases
- Finding insertion points for new elements
- Implementing other algorithms (merge sort, quicksort partitioning)
- Finding boundaries in sorted data
- Implementing standard library functions (bsearch, lower_bound, upper_bound)

## Advantages
- Very fast for large datasets: O(log n) time complexity
- Memory efficient: O(1) space for iterative version
- Simple to implement and understand

## Disadvantages
- Requires the array to be sorted
- Not suitable for unsorted data
- Recursive version uses O(log n) space due to function call stack