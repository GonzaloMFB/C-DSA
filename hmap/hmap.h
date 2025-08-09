#ifndef HMAP_H
#define HMAP_H

typedef struct Entry {
    int id;
    char* value;
    struct Entry* next;
} Entry;

typedef struct {
    int map_size;
    int count;
    Entry** entries;
} HMap;

// Creates and returns an empty hashmap
HMap create_map(int map_size);

// In a hashmap, inserts or updates a value under a certain key.
void insert(int key, char* value, HMap* map);
// In a hashmap, deletes a value under a certain key.
void del_entry(int key, HMap* map);
// In a hashmap, reads a value under a certain key.
char* get(int key, HMap* map);
// Delete the hashmap and its contents, freeing memory.
void cleanup(HMap* map);

#endif

