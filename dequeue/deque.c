#include <stdio.h>
#include <stdlib.h>

typedef struct Deque {
    int count;
    int front_idx;
    int back_idx;
    int max_length;
    int* array;
} Deque;

Deque* create_deque(int size) {
    Deque* deque = malloc(sizeof(Deque));
    if (deque == NULL) {
        fprintf(stderr, "MALLOC ERROR - Could not allocate %lu bytes", sizeof(Deque));
        return NULL;
    }
    deque->count = 0;
    deque->front_idx = size/2;
    deque->back_idx = size/2;
    deque->max_length = size;
    int* array = malloc(size*sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "MALLOC ERROR - Could not allocate %lu bytes", size * sizeof(int));
        free(deque);
        return NULL;
    }
    deque->array = array;
    return deque;
}

void destroy(Deque* deque) {
    free(deque->array);
    free(deque);
    deque = NULL;
}

void resize(Deque* deque) {
    deque->max_length *= 2;
    int* new_arr = malloc(deque->max_length * sizeof(int));
    if (new_arr == NULL) {
        fprintf(stderr, "MALLOC ERROR - Could not allocate %lu bytes", deque->max_length * sizeof(int));
        return;
    }
    int new_start = (deque->max_length/2 - deque->count/2);
    int j = 0;
    for (int i = deque->front_idx; i <= deque->back_idx; i++) {
        new_arr[new_start + j] = deque->array[i];
        j++;
    }
    free(deque->array);
    deque->array = new_arr;
    // TODO: Adjust the front and back index here.
    deque->front_idx = new_start;
    if (deque->count == 0) {
        deque->back_idx = new_start;
        return;
    }
    deque->back_idx = new_start + deque->count -1;
    
}

void push_front(int val, Deque* deque) {
    if (deque == NULL) {
        fprintf(stderr, "Must pass a valid Deque*");
        return;
    }
    if (deque->front_idx-1 < 0) {
        // trigger resize before decrementing pointer.
        resize(deque);
    }
    (deque->front_idx)--;
    // Insert 
    deque->array[deque->front_idx] = val;
    (deque->count)++;
    
}

void push_back(int val, Deque* deque) {
    if (deque == NULL) {
        fprintf(stderr, "Must pass a valid Deque*");
        return;
    }
    if (deque->back_idx +1 >= deque->max_length) {
        // trigger resize before decrementing pointer.
        resize(deque);
    }
    (deque->back_idx)++;
    // append at back like a stack.
    deque->array[deque->back_idx] = val;
    (deque->count)++;
}

void pop_front(Deque* deque) {
    // Just increment front counter
    if (deque == NULL) {
        fprintf(stderr, "Must pass a valid Deque*");
        return;
    }
    if (deque->count == 0) {
        fprintf(stderr, "Cannot pop from empty deque.");
        return;
    }
    (deque->front_idx)++;
    (deque->count)--;
}

void pop_back(Deque* deque) {
    // Just decrement back counter
    if (deque == NULL) {
        fprintf(stderr, "Must pass a valid Deque*");
        return;
    }
    if (deque->count == 0) {
        fprintf(stderr, "Cannot pop from empty deque.");
        return;
    }
    (deque->back_idx)--;
    (deque->count)--;
}