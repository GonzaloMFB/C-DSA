#include "vector.h"
#include <stdio.h>
#include <assert.h>

void test_map(Vector* vec) {
    assert(max_length(vec) == 8);
    append(1, vec);
    printf("Passed max_length tests\n");

    assert(length(vec) == 1);
    printf("Passed append test\n");
    printf("Passed length test\n");

    append(2, vec);
    assert(length(vec) == 2);
    assert(get(0, vec) == 1);
    printf("Passed get test\n");

    set(0, 19, vec);
    assert(get(0, vec) == 19);
    printf("Passed set test\n");

    insert(-45, 1, vec);
    assert(get(1, vec) == -45);
    assert(get(2, vec) == 2);
    printf("Passed insert test\n");

    pop(vec);
    assert(length(vec) == 2);
    printf("Passed pop test\n");

    for (int i = 100; i <= 106; i++) {
        append(i, vec);
    }
    assert(max_length(vec) == 16);
    printf("Passed resize test\n");



    clear(vec);
    assert(length(vec) == 0);
    printf("Passed clear test\n");

    destroy(vec);
    printf("Passed destroy test\n");
}

int main() {
    Vector vec = create(8);
    test_map(&vec);
    printf("All tests passed!\n");
    return 0;
}