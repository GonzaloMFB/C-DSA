#include "hmap.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


void test_insert(HMap* map) {
    // Tests both inserting a new key and updating it
    insert(1, "two", map);
    insert(1, "one", map);
    char* val = get(1, map);
    assert(strcmp(val, "one") == 0);
    printf("test_insert - PASSED\n");
    // fflush(stdout);
}

void test_delete(HMap* map) {
    // Tests whether we can delete at a particular key
    insert(2, "two", map);
    del_entry(2, map);
    char* val = get(2, map);
    assert(val == NULL);
    printf("test_delete - PASSED\n");
    // fflush(stdout);
}

void test_resize(HMap* map) {
    // Insert ints with value
    int start = 97; // Represents letter 'a'
    int end = start + 25; // Represents letter 'z'
    assert(map->count == 0);
    for (int i = 0; start + i <= end; i ++) {
        char val[2] = { (char)(start + i), '\0' };
        insert(start + i, val, map);
    }
    assert(map->count == 26);
    assert(map->map_size == 64);
    // Now, we test the entries are actually still on the map.
    for (int i = 0; i < map->count; i++) {
        int key = start + i;
        char* val = get(key, map);
        char expected[2] = { (char)(start + i), '\0' };
        assert(val != NULL);
        assert(strcmp(val, expected) == 0);
    }
    printf("test_resize - PASSED\n");
}

int main() {
    HMap test_map = create_map(16);
    test_insert(&test_map);
    test_delete(&test_map);
    test_map = create_map(16);
    test_resize(&test_map);
    printf("All tests passed!\n");
    cleanup(&test_map);
    return 0;
}