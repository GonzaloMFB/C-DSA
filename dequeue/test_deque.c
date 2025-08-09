#include <stdio.h>
#include <assert.h>
#include "deque.h"

void test_create_deque() {
    Deque* deque = create_deque(10);
    assert(deque != NULL);
    assert(deque->count == 0);
    assert(deque->max_length == 10);
    assert(deque->front_idx == 5);
    assert(deque->back_idx == 5);
    assert(deque->array != NULL);
    destroy(deque);
    printf("SUCCESS - test_create_deque passed\n");
}

void test_push_front_single() {
    Deque* deque = create_deque(10);
    push_front(42, deque);
    assert(deque->count == 1);
    assert(deque->front_idx == 4);
    assert(deque->back_idx == 5);
    destroy(deque);
    printf("SUCCESS - test_push_front_single passed\n");
}

void test_push_back_single() {
    Deque* deque = create_deque(10);
    push_back(42, deque);
    assert(deque->count == 1);
    assert(deque->front_idx == 5);
    assert(deque->back_idx == 6);
    destroy(deque);
    printf("SUCCESS - test_push_back_single passed\n");
}

void test_push_front_multiple() {
    Deque* deque = create_deque(10);
    push_front(1, deque);
    push_front(2, deque);
    push_front(3, deque);
    assert(deque->count == 3);
    assert(deque->front_idx == 2);
    assert(deque->back_idx == 5);
    destroy(deque);
    printf("SUCCESS - test_push_front_multiple passed\n");
}

void test_push_back_multiple() {
    Deque* deque = create_deque(10);
    push_back(1, deque);
    push_back(2, deque);
    push_back(3, deque);
    assert(deque->count == 3);
    assert(deque->front_idx == 5);
    assert(deque->back_idx == 8);
    destroy(deque);
    printf("SUCCESS - test_push_back_multiple passed\n");
}

void test_mixed_push_operations() {
    Deque* deque = create_deque(10);
    push_back(1, deque);
    push_front(2, deque);
    push_back(3, deque);
    push_front(4, deque);
    
    assert(deque->count == 4);
    assert(deque->front_idx == 3);
    assert(deque->back_idx == 7);
    destroy(deque);
    printf("SUCCESS - test_mixed_push_operations passed\n");
}

void test_pop_front() {
    Deque* deque = create_deque(10);
    push_back(1, deque);
    push_back(2, deque);
    push_back(3, deque);
    
    pop_front(deque);
    assert(deque->count == 2);
    assert(deque->front_idx == 6);
    assert(deque->back_idx == 8);
    
    destroy(deque);
    printf("SUCCESS - test_pop_front passed\n");
}

void test_pop_back() {
    Deque* deque = create_deque(10);
    push_back(1, deque);
    push_back(2, deque);
    push_back(3, deque);
    
    pop_back(deque);
    assert(deque->count == 2);
    assert(deque->front_idx == 5);
    assert(deque->back_idx == 7);
    
    destroy(deque);
    printf("SUCCESS - test_pop_back passed\n");
}

void test_pop_empty() {
    Deque* deque = create_deque(10);
    pop_front(deque);
    pop_back(deque);
    assert(deque->count == 0);
    destroy(deque);
    printf("SUCCESS - test_pop_empty passed\n");
}

void test_resize_front_buffer() {
    Deque* deque = create_deque(2);
    
    push_front(1, deque);
    int old_max = deque->max_length;
    push_front(2, deque);
    
    assert(deque->count == 2);
    assert(deque->max_length > old_max);
    
    destroy(deque);
    printf("SUCCESS - test_resize_front_buffer passed\n");
}

void test_resize_back_buffer() {
    Deque* deque = create_deque(2);
    
    push_back(1, deque);
    int old_max = deque->max_length;
    push_back(2, deque);
    
    assert(deque->count == 2);
    assert(deque->max_length > old_max);
    
    destroy(deque);
    printf("SUCCESS - test_resize_back_buffer passed\n");
}

void test_full_cycle() {
    Deque* deque = create_deque(10);
    
    push_back(1, deque);
    push_front(2, deque);
    push_back(3, deque);
    push_front(4, deque);
    
    pop_front(deque);
    pop_back(deque);
    
    assert(deque->count == 2);
    
    push_front(5, deque);
    push_back(6, deque);
    
    assert(deque->count == 4);
    
    destroy(deque);
    printf("SUCCESS - test_full_cycle passed\n");
}

int main() {
    printf("Running deque tests...\n\n");
    
    test_create_deque();
    test_push_front_single();
    test_push_back_single();
    test_push_front_multiple();
    test_push_back_multiple();
    test_mixed_push_operations();
    test_pop_front();
    test_pop_back();
    test_pop_empty();
    test_resize_front_buffer();
    test_resize_back_buffer();
    test_full_cycle();
    
    printf("\nSUCCESS - All deque tests passed!\n");
    return 0;
}