#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char letter; // We can keep track of the full trie prefix with an outside variable.
    int termination; // Indicates whether this could be a full word.
    int max_children;
    int num_children;
    struct Node** children; // Array of pointers to access all of a node's children.
} Node;

Node* create_node(char letter) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes of memory", sizeof(Node));
    }
    node->letter = letter;
    node->termination = 0; // not a word termination by default.
    // Max of 26 children, assuming lowercase english.
    // However, we'll waste space by setting the max by default.
    node->max_children = 8; 
    node->num_children = 0;
    Node** children = malloc(node->max_children * sizeof(Node*));
    if (children == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes of memory", node->max_children * sizeof(Node*));
        free(node);
    }
    node->children = children;
    return node;
}

void delete_trie(Node* node) {
    if (node == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid node.");
        return;
    }
    // Recurse on the children array to free each child node.
    for (int i = 0; i < node->num_children; i++) {
        delete_trie(node->children[i]);
    }
    free(node->children);
    node->children = NULL;
    free(node);
    node = NULL;
}

char check_letter(Node* node) {
    if (node == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid node.");
    }
    return node->letter;
}
int check_termination(Node* node) {
    if (node == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid node.");
    }
    return node->termination;
}
void toggle_termination(Node* node) {
    if (node == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid node.");
    }
    node->termination = (node->termination == 0) ? 1 : 0;
}
void resize(Node* node) {
    if (node == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid node.");
    }
    // Two resizing tiers: 8->16, 16->26
    // No more than 26 as 26 chars max, assuming lowercase english.
    node->max_children = (node->max_children == 8) ? 16 : 26;
    Node** new_arr = malloc(node->max_children * sizeof(Node*));
    if (new_arr == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes of memory on resize", node->max_children * sizeof(Node*));
    }
    for (int i = 0; i < node->num_children; i++){
        new_arr[i] = node->children[i];
    }
    free(node->children);
    node->children = new_arr;
}

void insert(char* word, Node* root) {
    if (root == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Node*.");
        return;
    }
    if (*word == '\0') {
        // Found null terminator, base case of recursion, leave.
        if (root->termination == 0) {
            root->termination = 1;
        }
        return;
    }
    // Insert char on current node and then go to that children.
    for (int i = 0; i < root->num_children; i++) {
        if (root->children[i]->letter == *word) {
            insert(word+1, root->children[i]);
            return;
        }
    }
    // Found no corresponding child node.
    // Create and add it.
    Node* child = create_node(*word);
    root->children[root->num_children] = child;
    root->num_children++;
    // Resize logic checks for 8 or 16 ch
    if (root->num_children == root->max_children && root->max_children != 26) {
        resize(root);
    }
    // And now, we get into that child node and do the recursion.
    insert(word+1, root->children[root->num_children-1]);
}

int search(char* word, Node* root) {
    if (root == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Node*.");
        return -1;
    }
    if (*word == '\0') {
        // Found null terminator.
        // If the node is a termination, return 1 (True), else 0 (False)
        return root->termination == 1 ? 1 : 0;
    }
    for (int i = 0; i < root->num_children; i++) {
        if (root->children[i]->letter == *word) {
            return search(word+1, root->children[i]);
        }
    }
    // Compatible child not found, so the word is not there.
    return 0;
}

int should_delete(Node* node) {
    if (node->num_children == 0 && node->termination == 0) {
        // Delete node.
        return 1;
    }
    return 0;
}

int delete(char* word, Node* root) {
    if (root == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Node*.");
        return -1;
    }
    if (*word == '\0') {
        // Found null terminator, base case of recursion
        // Check if we have children; if we don't, delete the node.
        root->termination = 0;
        return should_delete(root);
    }
    // Traverse down to children
    for (int i = 0; i < root->num_children; i++) {
        if (root->children[i]->letter == *word) {
            int to_del = delete(word+1, root->children[i]);
            // After that, we also run delete_or_remove in this node
            if (to_del == 1) {
                free(root->children[i]);
                // Shift all to the left 
                for (int j = i; j < root->num_children-1; j++) {
                    root->children[j] = root->children[j+1];
                }
                root->num_children--;
            }
            break;
        }
    }
    return should_delete(root);
}

void delete_word(char* word, Node* root) {
    // Wrapper to call search just once vs every recursion.
    if (search(word, root) != 1) {
        fprintf(stderr, "Trie does not contain word.");
        return;
    }
    return delete(word, root);
}