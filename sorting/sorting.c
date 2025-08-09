#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int* array, int count) {
    // Swap elements with its continuous until the array is sorted.
    while(1) {
        int swapped = 0;
        for (int i = 1; i < count; i++) {
            if (array[i-1] > array[i]) {
                // Swap
                int tmp = array[i-1];
                array[i-1] = array[i];
                array[i] = tmp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
        // In the worst case scenario, the largest element will always be at the end
        // after 1 pass. In the second pass, the second largest, and so on.
        // Decrease count to optimize the array passes.
        count--; 
    }
}

void selection_sort(int* array, int count) {
    // Select the minimum from the array, put at the starting position.
    // Increase the starting position, then run it again from it.
    for (int st = 0; st < count-1; st++) {
        int min_idx = st; // We start with st as the index with the minimum element.
        for (int i = st; i < count; i++) {
            if (array[i] < array[min_idx]) {
                // Update minimum element's index
                min_idx = i;
            }
        }
        // Swap minimum element with element at starting position.
        int tmp = array[st];
        array[st] = array[min_idx];
        array[min_idx] = tmp;
        // Increment starting position.
    }
}

void insertion_sort(int* array, int count) {
    // Pick element as key, compare w/elements to the left for insertion.
    // Shuffle elements to the right when needed to make room.
    // Start at 1 because element at 0 is sorted against nothing.
    for (int i = 1; i < count; i++) {
        int key = array[i];
        int j = i-1;
        while (j >= 0 && array[j] > key) {
            // Keep shifting while we find bigger values
            // Break if we don't or j is out of bounds.
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key; // j+1 because j could be -1
    }
}

void merge(int* array, int st, int mid, int ed) {
    // Declare extra space for an array where we'll keep the sorted merge
    // We'll later copy that to the final array.
    int* extra_space = malloc((ed-st+1) * sizeof(int));
    // Set one ptr per subarray to compare the elements.
    int ptr1 = st;
    int ptr2 = mid+1;
    // Set an idx to keep track of wherewe are in the extra space.
    int extra_idx = 0;
    while (ptr1 <= mid && ptr2 <= ed) {
        // Compare and assign the minimum value between arr[ptr1] and arr[ptr2]
        int res;
        if (array[ptr1] <= array[ptr2]) {
            res = array[ptr1];
            ptr1++;
        }
        else {
            res = array[ptr2];
            ptr2++;
        }
        // Assign to the extra space array.
        extra_space[extra_idx++] = res;
    }
    // Copy and paste any possible leftovers onto the extra space.
    while (ptr1 <= mid) {
        extra_space[extra_idx++] = array[ptr1];
        ptr1++;
    }
    while (ptr2 <= ed) {
        extra_space[extra_idx++] = array[ptr2];
        ptr2++;
    }

    // Now, copy from extra space to base array.
    for (int i = 0 ; i < (ed-st+1); i++) {
        array[st+i] = extra_space[i];
    }
    // After copying, free extra space.
    free(extra_space);
}

void merge_sort_step(int* array, int st, int ed) {
    // Divide and conquer.
    // Keep dividing the array until you reach base case (individual numbers)
    // Then, reform bigger and bigger, sorted blocks by merging them, until you merge
    // the last 2 (2 halves of the original array)
    if (st >= ed) {
        return; // 1 element or invalid range
    }
    int mid = (st+ed)/2; // C rounds down
    merge_sort_step(array, st, mid);
    merge_sort_step(array, mid+1, ed);
    merge(array, st, mid, ed);
}

void merge_sort(int* array, int count) {
    // Wrapper to match signature
    merge_sort_step(array, 0, count-1);
}

int partition(int* array, int st, int ed) {
    int pivot = array[ed];
    int i = st - 1;
    
    for (int j = st; j < ed; j++) {
        if (array[j] <= pivot) {
            i++;
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }
    
    int tmp = array[i + 1];
    array[i + 1] = array[ed];
    array[ed] = tmp;
    
    return i + 1;

}

void quick_sort_step(int* array, int st, int ed) {
    // Divide and conquer
    if (st >= ed) {
        // Base case
        return;
    }
    int pivot_idx = partition(array, st, ed);
    // Knowing the pivot idx, we know where the left and right portions are.
    // We do not include pivot_idx in either because it already is in its place after
    // the partition function.
    quick_sort_step(array, st, pivot_idx -1);
    quick_sort_step(array, pivot_idx +1, ed);
}

void quick_sort(int* array, int count) {
    // Wrapper to keep the API equal.
    quick_sort_step(array, 0, count-1);
}