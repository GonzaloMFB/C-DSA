# Hash Map (Hash Table)

A hash map is a data structure that implements an associative array, mapping keys to values using a hash function. This implementation uses separate chaining with linked lists to handle hash collisions, providing efficient key-value storage and retrieval.

## Data Structure Overview

Hash maps provide fast access to data by using a hash function to compute an index into an array of buckets:
- **Hash Function**: Converts keys into array indices
- **Buckets**: Array slots that store entries
- **Collision Resolution**: Uses linked lists (separate chaining)
- **Dynamic**: Supports insertion, deletion, and lookup operations

## Hash Map Structure

```c
typedef struct Entry {
    int id;              // Key for the entry
    char* value;         // String value stored
    struct Entry* next;  // Next entry in collision chain
} Entry;

typedef struct {
    int map_size;        // Number of buckets in the hash table
    int count;           // Number of entries currently stored
    Entry** entries;     // Array of entry pointers (buckets)
} HMap;
```

## Time Complexity

| Operation | Average Case | Worst Case | Description |
|-----------|--------------|------------|-------------|
| Insert | O(1) | O(n) | Add or update key-value pair |
| Get | O(1) | O(n) | Retrieve value by key |
| Delete | O(1) | O(n) | Remove key-value pair |
| Hash Function | O(1) | O(1) | Compute hash value |

**Note**: Worst case occurs when all keys hash to the same bucket (poor hash function or adversarial input).

## Space Complexity
- **Memory**: O(n) where n is the number of key-value pairs
- **Buckets**: O(m) where m is the map size (number of buckets)
- **Load Factor**: n/m (affects performance)

## Core Functions

### Hash Map Management
- `create_map(int map_size)` - Creates hash map with specified number of buckets
- `cleanup(HMap* map)` - Frees all memory used by the hash map

### Basic Operations
- `insert(int key, char* value, HMap* map)` - Inserts/updates key-value pair
- `get(int key, HMap* map)` - Retrieves value for given key (NULL if not found)
- `del_entry(int key, HMap* map)` - Removes key-value pair from map

## Usage Examples

### Basic Hash Map Operations

```c
#include "hmap.h"
#include <stdio.h>
#include <string.h>

int main() {
    // Create hash map with 10 buckets
    HMap map = create_map(10);
    
    // Insert key-value pairs
    insert(1, "Apple", &map);
    insert(2, "Banana", &map);
    insert(3, "Orange", &map);
    insert(12, "Grape", &map);  // May collide with key 2 (hash(12) % 10 = 2)
    
    printf("Map contains %d entries\n", map.count);
    
    // Retrieve values
    char* fruit1 = get(1, &map);
    char* fruit2 = get(2, &map);
    char* fruit12 = get(12, &map);
    
    if (fruit1) printf("Key 1: %s\n", fruit1);    // Output: Apple
    if (fruit2) printf("Key 2: %s\n", fruit2);    // Output: Banana
    if (fruit12) printf("Key 12: %s\n", fruit12); // Output: Grape
    
    // Update existing value
    insert(1, "Red Apple", &map);
    char* updated = get(1, &map);
    if (updated) printf("Updated Key 1: %s\n", updated);  // Output: Red Apple
    
    // Delete entry
    del_entry(2, &map);
    char* deleted = get(2, &map);
    if (!deleted) printf("Key 2 was successfully deleted\n");
    
    // Clean up
    cleanup(&map);
    return 0;
}
```

### Collision Handling Example

```c
void collision_demo() {
    HMap map = create_map(5);  // Small map to force collisions
    
    // These keys will likely collide
    insert(1, "Value 1", &map);
    insert(6, "Value 6", &map);  // hash(6) % 5 = 1 (same as hash(1) % 5)
    insert(11, "Value 11", &map); // hash(11) % 5 = 1 (same bucket again)
    
    // All values should still be retrievable
    printf("Key 1: %s\n", get(1, &map));   // Value 1
    printf("Key 6: %s\n", get(6, &map));   // Value 6
    printf("Key 11: %s\n", get(11, &map)); // Value 11
    
    cleanup(&map);
}
```

### Dictionary/Cache Implementation

```c
typedef struct {
    HMap cache;
    int max_size;
} SimpleCache;

SimpleCache* create_cache(int bucket_count, int max_entries) {
    SimpleCache* cache = malloc(sizeof(SimpleCache));
    cache->cache = create_map(bucket_count);
    cache->max_size = max_entries;
    return cache;
}

void cache_put(int key, char* value, SimpleCache* cache) {
    if (cache->cache.count >= cache->max_size) {
        // Simple eviction: remove first entry (not LRU)
        printf("Cache full - would need eviction policy\n");
        return;
    }
    insert(key, value, &cache->cache);
}

char* cache_get(int key, SimpleCache* cache) {
    return get(key, &cache->cache);
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_map test_map.c hmap.c
```

Run the tests:
```bash
./test_map
```

## Hash Function Details

The implementation likely uses a simple hash function such as:
```c
int hash(int key, int map_size) {
    return key % map_size;  // Simple modulo hashing
}
```

### Hash Function Properties
- **Deterministic**: Same key always produces same hash
- **Uniform Distribution**: Keys spread evenly across buckets
- **Fast Computation**: O(1) time complexity
- **Minimize Collisions**: Reduce keys mapping to same bucket

## Collision Resolution: Separate Chaining

When multiple keys hash to the same bucket:
1. **Linked List**: Each bucket contains a linked list of entries
2. **Insert**: Add new entry to the front of the list
3. **Search**: Traverse list comparing keys
4. **Delete**: Find and remove entry from list

### Advantages of Separate Chaining
- Simple implementation
- Handles any number of collisions
- Dynamic memory usage
- Easy deletion

### Disadvantages
- Extra memory for pointers
- Poor cache locality
- Performance degrades with many collisions

## Load Factor and Performance

**Load Factor** = Number of entries / Number of buckets

- **Low Load Factor (< 0.5)**: Fast operations, more memory usage
- **High Load Factor (> 1.0)**: Slower operations, memory efficient
- **Optimal Range**: 0.75 - 1.0 for good balance

## Applications

Hash maps are fundamental in many areas:

### System Programming
- **Symbol Tables**: Compiler variable/function lookups
- **Caching**: Store frequently accessed data
- **Databases**: Index structures for fast queries
- **Memory Management**: Object tracking and garbage collection

### Web Development
- **Session Storage**: User session data
- **Configuration**: Application settings
- **Routing Tables**: URL to handler mappings
- **API Rate Limiting**: Track request counts per client

### Algorithms
- **Frequency Counting**: Count occurrences of elements
- **Duplicate Detection**: Identify repeated items
- **Graph Algorithms**: Adjacency list representation
- **Dynamic Programming**: Memoization tables

## Advantages

1. **Fast Average Performance**: O(1) operations on average
2. **Flexible Keys**: Can hash various data types
3. **Dynamic Size**: Grows and shrinks as needed
4. **Memory Efficient**: Only stores actual key-value pairs
5. **Simple Interface**: Intuitive put/get/delete operations

## Disadvantages

1. **Worst Case Performance**: O(n) when many collisions occur
2. **No Ordering**: Keys are not stored in any particular order
3. **Hash Function Dependency**: Performance depends on good hash function
4. **Memory Overhead**: Extra space for pointers and unused buckets

## Comparison with Other Data Structures

| Feature | Hash Map | Array | Binary Search Tree |
|---------|----------|--------|-------------------|
| Search | O(1) avg | O(n) | O(log n) |
| Insert | O(1) avg | O(n) | O(log n) |
| Delete | O(1) avg | O(n) | O(log n) |
| Ordered | No | Yes (by index) | Yes |
| Memory | O(n) | O(n) | O(n) |

## Optimization Considerations

- **Choose Good Hash Function**: Minimize collisions
- **Appropriate Map Size**: Balance memory vs performance
- **Dynamic Resizing**: Grow/shrink based on load factor
- **Alternative Collision Resolution**: Open addressing, Robin Hood hashing