# Trie (Prefix Tree)

A trie is a tree-like data structure used to store and search strings efficiently. Also known as a prefix tree, it stores strings in a way that allows fast prefix-based operations, making it ideal for autocomplete, spell checkers, and dictionary applications.

## Data Structure Overview

A trie organizes strings by their characters:
- **Root Node**: Empty node representing the start
- **Path to Node**: Represents a prefix of stored strings
- **Termination Flag**: Marks nodes that represent complete words
- **Character-based Navigation**: Each edge represents a character

This implementation uses dynamic arrays for children, allowing it to handle any character set efficiently.

## Trie Structure

```c
typedef struct Node {
    char letter;         // Character stored in this node
    int termination;     // 1 if this node represents end of a word
    int max_children;    // Current capacity of children array
    int num_children;    // Number of children currently stored
    struct Node** children; // Dynamic array of child node pointers
} Node;
```

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Insert | O(m) | Insert word of length m |
| Search | O(m) | Search for word of length m |
| Delete | O(m) | Delete word of length m |
| Prefix Search | O(p) | Find all words with prefix of length p |
| Auto-complete | O(p + n) | Find n words with prefix of length p |

Where m = word length, p = prefix length, n = number of matching words

## Space Complexity
- **Memory**: O(ALPHABET_SIZE × N × M) worst case, where N is number of words and M is average length
- **Practical**: Much more space-efficient due to shared prefixes

## Core Functions

### Memory Management
- `create_node(char letter)` - Creates new node with given character
- `delete_trie(Node* node)` - Recursively frees entire trie structure

### Node Operations
- `check_letter(Node* node)` - Returns character stored in node
- `check_termination(Node* node)` - Returns 1 if node marks end of word
- `toggle_termination(Node* node)` - Toggles the termination flag
- `resize(Node* node)` - Expands children array when needed

### Word Operations
- `insert(char* word, Node* root)` - Adds word to the trie
- `search(char* word, Node* root)` - Returns 1 if word exists, 0 otherwise
- `delete_word(char* word, Node* root)` - Removes word from trie

## Usage Examples

### Basic Trie Operations

```c
#include "trie.h"
#include <stdio.h>
#include <string.h>

int main() {
    // Create root node (typically stores no character)
    Node* root = create_node('\0');
    
    // Insert words into the trie
    insert("cat", root);
    insert("car", root);
    insert("card", root);
    insert("care", root);
    insert("careful", root);
    insert("dog", root);
    insert("dogs", root);
    
    // Search for words
    printf("Search 'car': %s\n", search("car", root) ? "Found" : "Not found");
    printf("Search 'care': %s\n", search("care", root) ? "Found" : "Not found");
    printf("Search 'cart': %s\n", search("cart", root) ? "Found" : "Not found");
    
    // Output:
    // Search 'car': Found
    // Search 'care': Found
    // Search 'cart': Not found
    
    // Delete a word
    delete_word("car", root);
    printf("After deleting 'car': %s\n", search("car", root) ? "Found" : "Not found");
    printf("'care' still exists: %s\n", search("care", root) ? "Found" : "Not found");
    
    // Clean up
    delete_trie(root);
    return 0;
}
```

### Prefix Matching Implementation

```c
// Find all nodes that match a prefix (helper function)
Node* find_prefix_node(char* prefix, Node* root) {
    Node* current = root;
    
    for (int i = 0; prefix[i] != '\0'; i++) {
        int found = 0;
        // Search through children for matching character
        for (int j = 0; j < current->num_children; j++) {
            if (current->children[j]->letter == prefix[i]) {
                current = current->children[j];
                found = 1;
                break;
            }
        }
        if (!found) {
            return NULL;  // Prefix not found
        }
    }
    return current;
}

// Check if any words start with given prefix
int has_prefix(char* prefix, Node* root) {
    return find_prefix_node(prefix, root) != NULL;
}

// Collect all words with given prefix (simplified version)
void collect_words_with_prefix(Node* node, char* prefix, char* current_word, int depth) {
    if (node->termination) {
        current_word[depth] = '\0';
        printf("%s%s\n", prefix, current_word);
    }
    
    for (int i = 0; i < node->num_children; i++) {
        current_word[depth] = node->children[i]->letter;
        collect_words_with_prefix(node->children[i], prefix, current_word, depth + 1);
    }
}

void autocomplete(char* prefix, Node* root) {
    Node* prefix_node = find_prefix_node(prefix, root);
    if (prefix_node == NULL) {
        printf("No words found with prefix '%s'\n", prefix);
        return;
    }
    
    printf("Words starting with '%s':\n", prefix);
    char word_buffer[100];
    collect_words_with_prefix(prefix_node, prefix, word_buffer, 0);
}
```

### Dictionary Application

```c
typedef struct Dictionary {
    Node* root;
    int word_count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = malloc(sizeof(Dictionary));
    dict->root = create_node('\0');
    dict->word_count = 0;
    return dict;
}

void add_word(Dictionary* dict, char* word) {
    if (!search(word, dict->root)) {
        insert(word, dict->root);
        dict->word_count++;
        printf("Added '%s' to dictionary\n", word);
    } else {
        printf("'%s' already exists in dictionary\n", word);
    }
}

int is_valid_word(Dictionary* dict, char* word) {
    return search(word, dict->root);
}

void suggest_corrections(Dictionary* dict, char* word) {
    printf("Suggestions for '%s':\n", word);
    
    // Simple suggestions: try removing last character
    int len = strlen(word);
    if (len > 1) {
        char shorter[100];
        strncpy(shorter, word, len - 1);
        shorter[len - 1] = '\0';
        
        if (search(shorter, dict->root)) {
            printf("  %s\n", shorter);
        }
    }
    
    // Could add more sophisticated suggestions here
    // (character substitution, transposition, etc.)
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_trie test_trie.c trie.c
```

Run the tests:
```bash
./test_trie
```

## Implementation Details

### Dynamic Children Management
- Each node starts with a small children array
- Array doubles in size when capacity is exceeded
- Children are stored as pointers to allow heterogeneous characters

### Character Searching
- Linear search through children array for target character
- Could be optimized with sorted array + binary search
- For ASCII, could use direct indexing with 256-element array

### Memory Optimization
- Shared prefixes save significant memory
- Only complete words are marked with termination flag
- Nodes store actual characters for debugging/traversal

## Applications

Tries are particularly useful for:

### Text Processing
- **Autocomplete**: Search suggestions in text editors, browsers
- **Spell Checking**: Dictionary lookup and suggestion generation
- **Word Games**: Scrabble, crosswords, word search validation
- **Text Compression**: Pattern recognition and encoding

### System Software
- **IP Routing Tables**: Longest prefix matching for network routing
- **File Systems**: Directory structure and path resolution
- **Symbol Tables**: Compiler identifier management
- **Command Line**: Shell command and option completion

### Web Development
- **Search Engines**: Query suggestion and completion
- **URL Routing**: Web application route matching
- **Tag Systems**: Blog tags, social media hashtags
- **API Endpoints**: RESTful URL pattern matching

## Advantages

1. **Fast Prefix Operations**: Excellent for autocomplete and prefix matching
2. **Memory Efficient**: Shared prefixes reduce storage requirements
3. **Ordered Traversal**: In-order traversal gives lexicographically sorted results
4. **Predictable Performance**: O(m) operations regardless of dictionary size
5. **No Hash Collisions**: Unlike hash tables, no collision handling needed

## Disadvantages

1. **Memory Overhead**: Pointer storage for sparse character sets
2. **Cache Performance**: Tree structure can have poor cache locality
3. **Unbalanced Structure**: Performance depends on word distribution
4. **Complex Deletion**: Removing words requires careful node cleanup

## Comparison with Other Data Structures

| Feature | Trie | Hash Table | BST | Array |
|---------|------|------------|-----|-------|
| Search | O(m) | O(1) avg | O(log n) | O(n) |
| Insert | O(m) | O(1) avg | O(log n) | O(n) |
| Delete | O(m) | O(1) avg | O(log n) | O(n) |
| Prefix Search | O(p) | O(n) | O(n) | O(n) |
| Memory | O(nm) | O(n) | O(n) | O(n) |
| Ordered | Yes | No | Yes | If sorted |

Where m = word length, n = number of words, p = prefix length

## Optimization Techniques

### Memory Optimization
- **Compressed Tries**: Store common suffixes separately
- **Ternary Search Trees**: More memory-efficient alternative
- **Path Compression**: Skip nodes with single children

### Performance Optimization
- **Sorted Children**: Binary search instead of linear search
- **Hash Table Children**: O(1) child lookup for large alphabets
- **Lazy Deletion**: Mark nodes as deleted without removing immediately

## Variants and Extensions

### Compressed Trie (Radix Tree)
- Compress chains of single-child nodes
- More memory efficient for sparse tries
- Used in routing tables and file systems

### Ternary Search Tree
- Three-way branching: less than, equal, greater than
- More memory efficient than standard tries
- Good for variable-length alphabets

### Suffix Trie
- Store all suffixes of a string
- Useful for pattern matching and string analysis
- Foundation for more complex suffix structures