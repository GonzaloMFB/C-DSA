#ifndef TRIE_H
#define TRIE_H

typedef struct Node {
    char letter;
    int termination;
    int max_children;
    int num_children;
    struct Node** children;
} Node;

Node* create_node(char letter);
char check_letter(Node* node);
int check_termination(Node* node);
void toggle_termination(Node* node);
void resize(Node* node);
void insert(char* word, Node* root);
int search(char* word, Node* root);
void delete_trie(Node* node);
void delete_word(char* word, Node* root);

#endif