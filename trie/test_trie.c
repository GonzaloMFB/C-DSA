#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "trie.h"

void test_create_node() {
    printf("Testing create_node...\n");
    Node* node = create_node('a');
    
    assert(node != NULL);
    assert(node->letter == 'a');
    assert(node->termination == 0);
    assert(node->max_children == 8);
    assert(node->num_children == 0);
    assert(node->children != NULL);
    
    free(node->children);
    free(node);
    printf("SUCCESS - create_node tests passed\n");
}

void test_basic_operations() {
    printf("Testing basic node operations...\n");
    Node* node = create_node('b');
    
    assert(check_letter(node) == 'b');
    assert(check_termination(node) == 0);
    
    toggle_termination(node);
    assert(check_termination(node) == 1);
    
    toggle_termination(node);
    assert(check_termination(node) == 0);
    
    free(node->children);
    free(node);
    printf("SUCCESS - basic operations tests passed\n");
}

void test_insert_and_search_single_word() {
    printf("Testing insert and search with single word...\n");
    Node* root = create_node('\0');
    
    insert("cat", root);
    
    assert(search("cat", root) == 1);
    assert(search("ca", root) == 0);
    assert(search("cats", root) == 0);
    assert(search("dog", root) == 0);
    
    delete_trie(root);
    printf("SUCCESS - single word insert/search tests passed\n");
}

void test_insert_and_search_multiple_words() {
    printf("Testing insert and search with multiple words...\n");
    Node* root = create_node('\0');
    
    insert("cat", root);
    insert("car", root);
    insert("card", root);
    insert("care", root);
    
    assert(search("cat", root) == 1);
    assert(search("car", root) == 1);
    assert(search("card", root) == 1);
    assert(search("care", root) == 1);
    
    assert(search("ca", root) == 0);
    assert(search("cars", root) == 0);
    assert(search("dog", root) == 0);
    
    delete_trie(root);
    printf("SUCCESS - multiple words insert/search tests passed\n");
}

void test_prefix_words() {
    printf("Testing words that are prefixes of other words...\n");
    Node* root = create_node('\0');
    
    insert("cat", root);
    insert("cats", root);
    insert("caterpillar", root);
    
    assert(search("cat", root) == 1);
    assert(search("cats", root) == 1);
    assert(search("caterpillar", root) == 1);
    
    assert(search("ca", root) == 0);
    assert(search("cate", root) == 0);
    
    delete_trie(root);
    printf("SUCCESS - prefix words tests passed\n");
}

void test_empty_string() {
    printf("Testing empty string insertion and search...\n");
    Node* root = create_node('\0');
    
    insert("", root);
    assert(search("", root) == 1);
    
    insert("hello", root);
    assert(search("hello", root) == 1);
    assert(search("", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - empty string tests passed\n");
}

void test_single_character_words() {
    printf("Testing single character words...\n");
    Node* root = create_node('\0');
    
    insert("a", root);
    insert("i", root);
    insert("x", root);
    
    assert(search("a", root) == 1);
    assert(search("i", root) == 1);
    assert(search("x", root) == 1);
    assert(search("b", root) == 0);
    
    delete_trie(root);
    printf("SUCCESS - single character tests passed\n");
}

void test_duplicate_insertions() {
    printf("Testing duplicate word insertions...\n");
    Node* root = create_node('\0');
    
    insert("hello", root);
    insert("hello", root);
    insert("hello", root);
    
    assert(search("hello", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - duplicate insertion tests passed\n");
}

void test_resize_functionality() {
    printf("Testing resize functionality with many children...\n");
    Node* root = create_node('\0');
    
    char words[26][2];
    for (int i = 0; i < 26; i++) {
        words[i][0] = 'a' + i;
        words[i][1] = '\0';
        insert(words[i], root);
    }
    
    for (int i = 0; i < 26; i++) {
        assert(search(words[i], root) == 1);
    }
    
    delete_trie(root);
    printf("SUCCESS - resize functionality tests passed\n");
}

void test_delete_single_word() {
    printf("Testing delete single word...\n");
    Node* root = create_node('\0');
    
    insert("cat", root);
    assert(search("cat", root) == 1);
    
    delete_word("cat", root);
    assert(search("cat", root) == 0);
    
    delete_trie(root);
    printf("SUCCESS - delete single word tests passed\n");
}

void test_delete_with_shared_prefix() {
    printf("Testing delete with shared prefixes...\n");
    Node* root = create_node('\0');
    
    insert("car", root);
    insert("card", root);  
    insert("care", root);
    
    delete_word("card", root);
    assert(search("card", root) == 0);
    assert(search("car", root) == 1);
    assert(search("care", root) == 1);
    
    delete_word("car", root);
    assert(search("car", root) == 0);
    assert(search("care", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - delete with shared prefix tests passed\n");
}

void test_delete_prefix_word() {
    printf("Testing delete word that is prefix of another...\n");
    Node* root = create_node('\0');
    
    insert("cat", root);
    insert("cats", root);
    
    delete_word("cat", root);
    assert(search("cat", root) == 0);
    assert(search("cats", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - delete prefix word tests passed\n");
}

void test_delete_longer_word() {
    printf("Testing delete longer word keeping prefix...\n");
    Node* root = create_node('\0');
    
    insert("cat", root);
    insert("cats", root);
    
    delete_word("cats", root);
    assert(search("cats", root) == 0);
    assert(search("cat", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - delete longer word tests passed\n");
}

void test_delete_nonexistent_word() {
    printf("Testing delete non-existent word...\n");
    Node* root = create_node('\0');
    
    insert("cat", root);
    delete_word("dog", root);
    assert(search("cat", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - delete non-existent word tests passed\n");
}

void test_delete_cascading_cleanup() {
    printf("Testing cascading cleanup after delete...\n");
    Node* root = create_node('\0');
    
    insert("abc", root);
    delete_word("abc", root);
    assert(search("abc", root) == 0);
    
    insert("hello", root);
    assert(search("hello", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - cascading cleanup tests passed\n");
}

void test_delete_multiple_operations() {
    printf("Testing multiple delete operations...\n");
    Node* root = create_node('\0');
    
    insert("apple", root);
    insert("app", root);
    insert("application", root);
    insert("apply", root);
    
    delete_word("application", root);
    assert(search("application", root) == 0);
    assert(search("apple", root) == 1);
    assert(search("app", root) == 1);
    assert(search("apply", root) == 1);
    
    delete_word("app", root);
    assert(search("app", root) == 0);
    assert(search("apple", root) == 1);
    assert(search("apply", root) == 1);
    
    delete_trie(root);
    printf("SUCCESS - multiple delete operations tests passed\n");
}

int main() {
    printf("Running Trie Tests\n");
    printf("==================\n");
    
    test_create_node();
    test_basic_operations();
    test_insert_and_search_single_word();
    test_insert_and_search_multiple_words();
    test_prefix_words();
    test_empty_string();
    test_single_character_words();
    test_duplicate_insertions();
    test_resize_functionality();
    test_delete_single_word();
    test_delete_with_shared_prefix();
    test_delete_prefix_word();
    test_delete_longer_word();
    test_delete_nonexistent_word();
    test_delete_cascading_cleanup();
    test_delete_multiple_operations();
    
    printf("\nSUCCESS - All tests passed!\n");
    return 0;
}