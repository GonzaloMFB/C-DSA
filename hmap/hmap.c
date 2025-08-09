#include <stdio.h>
#include <stdlib.h>
/*
Hash map implementation using bucketing.
*/
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

void resize(HMap* map);
void insert(int key, char* value, HMap* map);

HMap create_map(int map_size){
    HMap test;
    test.map_size = map_size;
    test.entries = malloc(test.map_size * sizeof(Entry*));
    for (int i = 0; i < test.map_size; i++) {
        test.entries[i] = NULL;
    }
    return test;
}

int hash(int key, int map_size) {
    return key % map_size;
}

void resize(HMap* map) {
    // We will be updating the map.
    // First, store the old list.
    Entry** old_entries = map->entries;
    int old_size = map->map_size;
    // Now, we reset the hash map. We will resize to double memory.
    map->map_size = old_size * 2;
    map->count = 0;
    Entry** new_entries = malloc(map->map_size * sizeof(Entry*));
    for (int i = 0; i < map->map_size; i++) {
        new_entries[i] = NULL;
    }
    map->entries = new_entries;
    // Reinserting all elements:
    for (int i = 0; i < old_size; i++) {
        // Now we need to iterate through the linked list in the node
        Entry* current = old_entries[i];
        while (current != NULL) {
            // Get the key, val, insert.
            Entry* next = current->next;
            int key = current->id;
            char* value = current->value;
            insert(key, value, map);
            // Free the entry at addr current, and then continue onto the next node.
            free(current);
            current = next;
        }
    }
    free(old_entries);
    
}

void insert(int key, char* value, HMap* map) {
    // First, we hash the key
    int hkey = hash(key, map->map_size);
    if (map->entries[hkey] == NULL) {
        Entry* new_entry = malloc(sizeof(Entry));
        new_entry->id = key;
        new_entry->value = value;
        new_entry->next = NULL;
        map->entries[hkey] = new_entry;
        map->count += 1;
        if (map->count >= 0.7 * map->map_size) {
            resize(map);
        }
        return;
    }
    Entry* current = map->entries[hkey];
    while (current != NULL) {
        // If we find a match, update the value
        if (current->id == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    // We reached the end of the linked list, and found no matches.
    // Hence, we insert at the beginning.
    Entry* new_entry = malloc(sizeof(Entry));
    new_entry->id = key;
    new_entry->value = value;
    new_entry->next = map->entries[hkey]; // points at the old one
    map->entries[hkey] = new_entry; // reassigns the external bucket to point at the new one.
    map->count += 1;
    if (map->count >= 0.7 * map->map_size) {
        resize(map);
    }
}

void del_entry(int key, HMap* map) {
    int hkey = hash(key, map->map_size);
    Entry* current = map->entries[hkey];
    Entry* prev = NULL;
    while (current != NULL) {
        if (current->id == key) {
            // Break the link
            if (prev == NULL) {
                // First node, 
                map->entries[hkey] = current->next;
            }
            else {
                prev->next = current->next;
            }
            map->count -= 1;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    // Found no matches to delete.
    return;
}

char* get(int key, HMap* map) {
    int hkey = hash(key, map->map_size);
    Entry* current = map->entries[hkey];
    while (current != NULL) {
        if (current->id == key) {
            return current->value;
        }
        current = current->next;
    }
    // Found no matches, return NULL instead.
    return NULL;
}

void cleanup(HMap* map) {
    // We have malloc'd each Entry and the Entries array
    // Iterate using map_size, as we may have empty initialized entries.
    for (int i = 0; i < map->map_size; i++) {
        // Now we need to iterate through the linked list in the node
        Entry* current = map->entries[i];
        while (current != NULL) {
            // Get the key, val, insert.
            Entry* next = current->next;
            // Free the entry at addr current, and then continue onto the next node.
            free(current);
            current = next;
        }
    }
    free(map->entries);
}
