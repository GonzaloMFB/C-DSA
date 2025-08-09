#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* create_node(int val) {
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    return node;
}

void prepend(int val, Node** list) {
    if (list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a pointer of Node\n");
        return;
    }
    Node* node = create_node(val);
    node->next = *list;
    *list = node;
}

void append(int val, Node* list) {
    if (list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return;
    }
    Node* node = create_node(val);
    // Iterate through the whole list and update the last value.
    while (list->next != NULL) {
        list = list->next;
    }
    list->next = node;
}

int get_at(int index, Node* list) {
    if (list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return -1;
    }
    int i = 0;
    while (list != NULL) {
        if (i == index) {
            return list->val;
        }
        i++;
        list = list->next;
    }

    fprintf(stderr, "Index %d is out of bounds\n", index);
    return -1;
}

Node* find_value(int target, Node* list) {
    if (list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return NULL;
    }
    while (list != NULL) {
        if (list->val == target) {
            return list;
        }
        list = list->next;
    }
    // Return NULL if it didn't find anything.
    return NULL;
}

int length(Node* list) {
    if (list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return -1;
    }
    int len = 0;
    while (list != NULL) {
        len++;
        list = list->next;
    }
    return len;
}

void destroy(Node* list) {
    if (list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return;
    }
    while (list != NULL) {
        Node* next = list->next;
        free(list);
        list = next;
    }
}

void remove_at_index(int index, Node** list) {
    if (*list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return;
    }
    if (index < 0 || index > length(*list)-1) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    Node* current = *list;
    if (index == 0) {
        // Head insertion. List node is the new node's next.
        Node* tmp = current->next;
        free(*list);
        *list = tmp;
        return;
    }

    int i = 0;
    current = (*list)->next;
    Node* prev = *list;
    while (current != NULL) {
        if (i == index) {
            if (prev != NULL) {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        i++;
        prev = current;
        current = current->next;
    }

}

void insert_at_index(int index, int val, Node** list) {
    if (*list == NULL) {
        fprintf(stderr, "You must pass a valid pointer to a Node\n");
        return;
    }
    if (index < 0 || index > length(*list)-1) {
        fprintf(stderr, "Index out of bounds. Use append if you wish to insert at the end.\n");
        return;
    }
    Node* new_node = create_node(val);
    if (index == 0) {
        // Head insertion. List node is the new node's next.
        new_node->next = *list;
        *list = new_node;
        return;
    }
    int i = 0;
    Node* current = *list;
    while (current != NULL) {
        if (i == index -1) {
            Node* tmp = current->next;
            new_node->next = tmp;
            current->next = new_node;
            return;
        }
        current = current->next;
    }

}