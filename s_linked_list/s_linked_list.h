#ifndef S_LINKED_LIST
#define S_LINKED_LIST

typedef struct Node {
    int val;
    struct Node* next;
} Node;

// Creates node (can nbe head of linked list)
Node* create_node(int val);

// Adds value at the beginning of the list
void prepend(int val, Node** list);

// Adds value at the end of the list
void append(int val, Node* list);

// Gets value from list at the given index
int get_at(int index, Node* list);

// Gets a pointer to the node that contains the target.
// NULL if no nodes have it.
Node* find_value(int target, Node* list);

// Returns length of linked list.
int length(Node* list);

// Destroys Linked List and frees up memory.
void destroy(Node* list);

// Removes element at given index, then shifts what's after it to the left.
void remove_at_index(int index, Node** list);

// Adds element at given index, then shifts what's after it to the right.
void insert_at_index(int index, int val, Node** list);

#endif