#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* next;
    struct Node* prev;
} Node;

Node* create_node(int val) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes of memory", sizeof(Node));
        return NULL;
    }
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

int length(Node* head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

int get(int index, Node* head) {
    int i = 0;
    if (index < 0 || index >= length(head)) {
        fprintf(stderr, "Index out of bounds.");
        return -1; // Sentinel value
    }
    while (head != NULL) {
        if (i == index) {
            return head->val;
        }
        i++;
        head = head->next;
    }
}

void set(int val, int index, Node* head) {
    int i = 0;
    if (index < 0 || index >= length(head)) {
        fprintf(stderr, "Index out of bounds.");
        return;
    }
    while (head != NULL) {
        if (i == index) {
            head->val = val;
        }
        i++;
        head = head->next;
    }
}

void prepend(int val, Node** head) {
    if (head == NULL) {
        fprintf(stderr, "head argument must be a valid pointer to a Node*");
        return;
    }
    // Inserts at beginning.
    Node* new_node = create_node(val);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    (*head)->prev = new_node;
    new_node->next = *head;
    *head = new_node;
}

void append(int val, Node* head) {
    if (head == NULL) {
        fprintf(stderr, "head argument must be a valid pointer to a Node");
        return;
    }
    while (head->next != NULL) {
        head = head->next;
    }
    // Now that we're at last node, append the new node.
    Node* new_node = create_node(val);
    new_node->prev = head;
    head->next = new_node;

}

void destroy(Node** head) {
    if (*head == NULL) {
        fprintf(stderr, "head argument must be a valid pointer to a Node*");
        return;
    }
    while (*head != NULL) {
        // Frees the memory at the pointer's address.
        // Ptr itself does not change, it points to freed (dangling) memory.
        Node* next = (*head)->next;
        free(*head);
        *head = next;
    }
    *head = NULL;
}

void remove_at_index(int index, Node** head) {
    if (*head == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return;
    }
    if (index < 0 || index >= length(*head)) {
        fprintf(stderr, "Index out of bounds.");
        return;
    }
    // First, case where the head is the node to remove.
    Node* current = *head;
    if (index == 0) {
        Node* tmp = current->next;
        free(*head);
        *head = tmp;
        // Update the new node's prev to NULL, since it's now the first
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        return;
    }
    // Traverse until given index, then delete node.
    // Just modify next and prev pointers of adjacent nodes.
    int i = 0;
    while (current != NULL) {
        if (i == index) {
            // Removal
            Node* prev = current->prev;
            Node* next = current->next;
            free(current);
            // Update the adjacent nodes of the removed node to point to each other.
            if (prev != NULL) {
                prev->next = next;
            }
            if (next != NULL) {
                next->prev = prev;
            }
            return;
        }
        i++;
        current = current->next;
    }
}

void insert_at_index(int index, int val, Node** head) {
    if (*head == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return;
    }
    int len = length(*head);
    if (index < 0 || index >= len) {
        fprintf(stderr, "Index out of bounds.");
        if (length(*head) == index) {
            printf("Use append to insert at end of Linked List.");
        }
        return;
    }
    // Traverse until given index, then add node
    // Modify next and prev pointer of the adjacent nodes
    Node* current = *head;
    Node* new_node = create_node(val);
    if (index == 0) {
        new_node->next = current;
        if (current != NULL) {
            // This would happen on empty linked list.
            current->prev = new_node;
        }
        *head = new_node;
        return;
    }
    int i = 1;
    while (current != NULL) {
        if (i == index) {
            // Insert node
            Node* prev = current->prev;
            Node* next = current->next;
            new_node->prev = prev;
            new_node->next = next;
            if (prev != NULL) {
                prev->next = new_node;
            }
            if (next != NULL) {
                next->prev = new_node;
            }
            return;
        }
        i++;
        current = current->next;
    }
}