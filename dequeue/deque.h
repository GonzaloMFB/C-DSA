#ifndef DEQUE_H
#define DEQUE_H

typedef struct Deque {
    int count;
    int front_idx;
    int back_idx;
    int max_length;
    int* array;
} Deque;

Deque* create_deque(int size);
void destroy(Deque* deque);
void resize(Deque* deque);
void push_front(int val, Deque* deque);
void push_back(int val, Deque* deque);
void pop_front(Deque* deque);
void pop_back(Deque* deque);

#endif