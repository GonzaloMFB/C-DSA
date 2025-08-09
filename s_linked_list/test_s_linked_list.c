#include "s_linked_list.h"
#include <stdio.h>
#include <assert.h>

void test_linked_list(Node* head) {
    assert(length(head) == 1);
    printf("    -> Passed creation\n");

    prepend(0, &head);
    assert(length(head) == 2);
    assert(get_at(0, head) == 0);
    printf("    -> Passed prepend and get_at\n");

    append(2, head);
    assert(length(head) == 3);
    assert(find_value(2, head) != NULL);
    printf("    -> Passed prepend and find_value\n");

    remove_at_index(1, &head);
    assert(length(head) == 2);
    assert(find_value(1, head) == NULL);
    printf("    -> Passed remove_at_index\n");

    insert_at_index(1, 17000, &head);
    assert(length(head) == 3);
    assert(find_value(17000, head) != NULL);
    printf("    -> Passed insert_at_index\n");

    destroy(head);
    printf("    -> Passed destroy\n");

}

int main() {
    printf("Starting tests...\n");
    Node* head = create_node(0);
    test_linked_list(head);
    printf("All tests passed!\n");
    return 0;
}