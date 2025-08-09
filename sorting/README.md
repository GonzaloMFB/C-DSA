# Sorting Algorithms

A comprehensive collection of fundamental sorting algorithms implemented in C. This library provides various approaches to sorting data, each with different time and space complexity characteristics, making them suitable for different scenarios.

## Algorithm Overview

Sorting algorithms arrange elements in a specific order (typically ascending or descending). This implementation includes both comparison-based and divide-and-conquer algorithms, showcasing different algorithmic paradigms and their trade-offs.

## Implemented Algorithms

### 1. Bubble Sort
**Paradigm**: Comparison-based, iterative
**Description**: Repeatedly steps through the list, compares adjacent elements and swaps them if they're in the wrong order.

### 2. Selection Sort  
**Paradigm**: Comparison-based, selection-based
**Description**: Finds the minimum element and places it at the beginning, then repeats for the remainder.

### 3. Insertion Sort
**Paradigm**: Comparison-based, incremental
**Description**: Builds the sorted array one item at a time, inserting each element into its proper position.

### 4. Merge Sort
**Paradigm**: Divide and conquer, recursive
**Description**: Divides the array into halves, sorts them recursively, then merges the sorted halves.

### 5. Quick Sort
**Paradigm**: Divide and conquer, partition-based
**Description**: Selects a pivot element and partitions the array around it, then recursively sorts the partitions.

## Time and Space Complexity

| Algorithm | Best Case | Average Case | Worst Case | Space Complexity | Stable |
|-----------|-----------|--------------|------------|------------------|---------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |

## Core Functions

- `bubble_sort(int* array, int count)` - Bubble sort implementation
- `selection_sort(int* array, int count)` - Selection sort implementation
- `insertion_sort(int* array, int count)` - Insertion sort implementation
- `merge_sort(int* array, int count)` - Merge sort implementation
- `quick_sort(int* array, int count)` - Quick sort implementation

## Usage Examples

### Basic Sorting Operations

```c
#include "sorting.h"
#include <stdio.h>
#include <string.h>

void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int original[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(original) / sizeof(original[0]);
    
    printf("Original array: ");
    print_array(original, size);
    
    // Test different sorting algorithms
    int arr[7];
    
    // Bubble Sort
    memcpy(arr, original, sizeof(original));
    bubble_sort(arr, size);
    printf("Bubble Sort:   ");
    print_array(arr, size);
    
    // Selection Sort
    memcpy(arr, original, sizeof(original));
    selection_sort(arr, size);
    printf("Selection Sort: ");
    print_array(arr, size);
    
    // Insertion Sort
    memcpy(arr, original, sizeof(original));
    insertion_sort(arr, size);
    printf("Insertion Sort: ");
    print_array(arr, size);
    
    // Merge Sort
    memcpy(arr, original, sizeof(original));
    merge_sort(arr, size);
    printf("Merge Sort:     ");
    print_array(arr, size);
    
    // Quick Sort
    memcpy(arr, original, sizeof(original));
    quick_sort(arr, size);
    printf("Quick Sort:     ");
    print_array(arr, size);
    
    return 0;
}
```

### Performance Comparison

```c
#include <time.h>
#include <stdlib.h>

void performance_test() {
    const int sizes[] = {100, 1000, 5000};
    const int num_sizes = 3;
    
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        int* arr = malloc(size * sizeof(int));
        int* test_arr = malloc(size * sizeof(int));
        
        // Generate random data
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 1000;
        }
        
        printf("\nTesting with %d elements:\n", size);
        
        // Test each algorithm
        clock_t start, end;
        
        // Bubble Sort (skip for large arrays - too slow)
        if (size <= 1000) {
            memcpy(test_arr, arr, size * sizeof(int));
            start = clock();
            bubble_sort(test_arr, size);
            end = clock();
            printf("Bubble Sort:    %.4f seconds\n", 
                   ((double)(end - start)) / CLOCKS_PER_SEC);
        }
        
        // Quick Sort
        memcpy(test_arr, arr, size * sizeof(int));
        start = clock();
        quick_sort(test_arr, size);
        end = clock();
        printf("Quick Sort:     %.4f seconds\n", 
               ((double)(end - start)) / CLOCKS_PER_SEC);
        
        // Merge Sort
        memcpy(test_arr, arr, size * sizeof(int));
        start = clock();
        merge_sort(test_arr, size);
        end = clock();
        printf("Merge Sort:     %.4f seconds\n", 
               ((double)(end - start)) / CLOCKS_PER_SEC);
        
        free(arr);
        free(test_arr);
    }
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_sorting test_sorting.c sorting.c
```

Run the tests:
```bash
./test_sorting
```

## Algorithm Details

### Bubble Sort
- **How it works**: Compares adjacent elements and swaps if out of order
- **Optimization**: Can stop early if no swaps made in a pass
- **Best for**: Educational purposes, very small datasets
- **Characteristics**: Simple, stable, adaptive

### Selection Sort
- **How it works**: Finds minimum element and places it at the beginning
- **Performance**: Always O(n²) regardless of input
- **Best for**: Situations where swap cost is high
- **Characteristics**: Simple, not stable, not adaptive

### Insertion Sort
- **How it works**: Inserts each element into its proper position in sorted portion
- **Performance**: Excellent on nearly sorted data
- **Best for**: Small datasets, nearly sorted data, online sorting
- **Characteristics**: Simple, stable, adaptive, in-place

### Merge Sort
- **How it works**: Recursively divides array, then merges sorted halves
- **Performance**: Guaranteed O(n log n) in all cases
- **Best for**: Large datasets, when stability is required
- **Characteristics**: Stable, predictable performance, requires extra space

### Quick Sort
- **How it works**: Partitions around pivot, recursively sorts partitions
- **Performance**: Average O(n log n), but O(n²) worst case
- **Best for**: General-purpose sorting, large datasets
- **Characteristics**: Fast average case, in-place, not stable

## When to Use Which Algorithm

### Small Arrays (n < 50)
- **Insertion Sort**: Fast for small, nearly sorted data
- **Selection Sort**: When memory writes are expensive

### Medium Arrays (50 < n < 10,000)
- **Quick Sort**: General purpose, good average performance
- **Merge Sort**: When stability is required

### Large Arrays (n > 10,000)
- **Quick Sort**: Usually fastest in practice
- **Merge Sort**: Predictable performance, stable
- **Hybrid Approaches**: Many libraries use Introsort (Quick + Heap + Insertion)

### Special Cases
- **Nearly Sorted**: Insertion Sort (O(n) best case)
- **Stability Required**: Merge Sort or Bubble Sort
- **Memory Constrained**: In-place algorithms (Quick, Selection, Insertion, Bubble)
- **Worst-case Guarantee**: Merge Sort or Heap Sort

## Stability in Sorting

**Stable Sort**: Maintains relative order of equal elements
- **Stable**: Bubble Sort, Insertion Sort, Merge Sort
- **Unstable**: Selection Sort, Quick Sort (typical implementation)

Example of stability importance:
```
Original: [(3,a), (1,b), (3,c), (2,d)]
Stable:   [(1,b), (2,d), (3,a), (3,c)]  // (3,a) before (3,c)
Unstable: [(1,b), (2,d), (3,c), (3,a)]  // order of equal elements changed
```

## Applications

### System Software
- **Database Systems**: Sorting query results
- **Operating Systems**: Process scheduling, file systems
- **Compilers**: Symbol table management
- **Graphics**: Z-buffer sorting, polygon sorting

### Data Processing
- **Search Optimization**: Sorted data enables binary search
- **Data Analysis**: Ranking, percentile calculations
- **Merge Operations**: Combining sorted datasets
- **Duplicate Removal**: Easier on sorted data

## Optimization Techniques

### Algorithm Improvements
- **Hybrid Sorting**: Switch algorithms based on array size
- **Three-way Partitioning**: Handle duplicate keys efficiently in Quick Sort
- **Natural Merge Sort**: Take advantage of existing sorted runs
- **Parallel Sorting**: Multi-threaded implementations

### Implementation Optimizations
- **Tail Call Optimization**: Reduce recursion stack in Quick Sort
- **Insertion Sort Cutoff**: Switch to insertion sort for small subarrays
- **Median-of-Three**: Better pivot selection in Quick Sort
- **Bottom-up Merge Sort**: Iterative implementation to avoid recursion