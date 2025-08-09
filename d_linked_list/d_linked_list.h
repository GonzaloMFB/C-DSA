#ifndef D_LINKED_LIST
#define D_LINKED_LIST

typedef struct Node {
    int val;
    struct Node* next;
    struct Node* prev;
} Node;

// Create node for doubly linked list
Node* create_node(int val);
// Get list length
int length(Node* head);
// Get element at index
int get(int index, Node* head);
// Set value at index.
void set(int val, int index, Node* head);
// Add to the beginning of the list.
void prepend(int val, Node** head);
// Add to the end of the list.
void append(int val, Node* head);
// Destroy and clean up the linked list.
void destroy(Node** head);
// Remove element at index. 
void remove_at_index(int index, Node** head);
// Insert element at index.
void insert_at_index(int index, int val, Node** head);

#endif