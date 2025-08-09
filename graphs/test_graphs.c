#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graphs.h"

// Test node creation
void test_create_node() {
    printf("Testing node creation...\n");
    
    Node* node = create_node(42);
    assert(node != NULL);
    assert(node->val == 42);
    assert(node->num_connected == 0);
    assert(node->adj_length == 8);
    assert(node->adj_list != NULL);
    
    clear_node(node);
    printf(" Node creation test passed\n");
}

// Test graph creation
void test_create_graph() {
    printf("Testing graph creation...\n");
    
    Graph* graph = create_graph();
    assert(graph != NULL);
    assert(graph->num_nodes == 0);
    assert(graph->max_size == 8);
    assert(graph->nodes != NULL);
    
    destroy(graph);
    printf(" Graph creation test passed\n");
}

// Test adding nodes to graph
void test_add_node_to_graph() {
    printf("Testing adding nodes to graph...\n");
    
    Graph* graph = create_graph();
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    
    add_node_to_graph(node1, graph);
    assert(graph->num_nodes == 1);
    assert(graph->nodes[0] == node1);
    
    add_node_to_graph(node2, graph);
    assert(graph->num_nodes == 2);
    assert(graph->nodes[1] == node2);
    
    destroy(graph);
    printf(" Add node to graph test passed\n");
}

// Test edge creation
void test_add_edge() {
    printf("Testing edge creation...\n");
    
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    
    add_edge(node1, node2);
    
    // Check bidirectional connection
    assert(node1->num_connected == 1);
    assert(node2->num_connected == 1);
    assert(node1->adj_list[0] == node2);
    assert(node2->adj_list[0] == node1);
    
    clear_node(node1);
    clear_node(node2);
    printf(" Edge creation test passed\n");
}

// Test duplicate edge prevention
void test_duplicate_edge() {
    printf("Testing duplicate edge prevention...\n");
    
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    
    add_edge(node1, node2);
    add_edge(node1, node2);  // Try to add same edge again
    
    // Should still only have one connection each
    assert(node1->num_connected == 1);
    assert(node2->num_connected == 1);
    
    clear_node(node1);
    clear_node(node2);
    printf(" Duplicate edge prevention test passed\n");
}

// Test self-loop prevention
void test_self_loop() {
    printf("Testing self-loop prevention...\n");
    
    Node* node = create_node(1);
    add_edge(node, node);  // Try to connect node to itself
    
    // Should have no connections
    assert(node->num_connected == 0);
    
    clear_node(node);
    printf(" Self-loop prevention test passed\n");
}

// Test check_visited function
void test_check_visited() {
    printf("Testing check_visited function...\n");
    
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    
    Node* visited[3];
    visited[0] = node1;
    visited[1] = node2;
    
    assert(check_visited(node1, visited, 2) == 1);  // Should be found
    assert(check_visited(node2, visited, 2) == 1);  // Should be found
    assert(check_visited(node3, visited, 2) == 0);  // Should not be found
    
    clear_node(node1);
    clear_node(node2);
    clear_node(node3);
    printf(" Check visited test passed\n");
}

// Test remove edge
void test_remove_edge() {
    printf("Testing edge removal...\n");
    
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    
    // Create connections: 1-2, 1-3
    add_edge(node1, node2);
    add_edge(node1, node3);
    
    assert(node1->num_connected == 2);
    assert(node2->num_connected == 1);
    
    // Remove edge between node1 and node2
    remove_edges(node1, node2);
    
    assert(node2->num_connected == 0);  // node2 should have no connections
    assert(node1->num_connected == 1);  // node1 still has connection to node3
    
    clear_node(node1);
    clear_node(node2);
    clear_node(node3);
    printf(" Edge removal test passed\n");
}

// Test complete graph scenario
void test_complete_graph() {
    printf("Testing complete graph scenario...\n");
    
    Graph* graph = create_graph();
    Node* nodes[4];
    
    // Create 4 nodes
    for (int i = 0; i < 4; i++) {
        nodes[i] = create_node(i + 1);
        add_node_to_graph(nodes[i], graph);
    }
    
    // Connect them: 1-2, 2-3, 3-4, 4-1 (cycle)
    add_edge(nodes[0], nodes[1]);
    add_edge(nodes[1], nodes[2]);
    add_edge(nodes[2], nodes[3]);
    add_edge(nodes[3], nodes[0]);
    
    assert(graph->num_nodes == 4);
    assert(nodes[0]->num_connected == 2);  // Connected to 2 and 4
    assert(nodes[1]->num_connected == 2);  // Connected to 1 and 3
    
    destroy(graph);
    printf(" Complete graph scenario test passed\n");
}

// Test graph traversal (basic connectivity test)
void test_graph_traversal() {
    printf("Testing graph traversal...\n");
    
    Graph* graph = create_graph();
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    
    add_node_to_graph(node1, graph);
    add_node_to_graph(node2, graph);
    add_node_to_graph(node3, graph);
    
    add_edge(node1, node2);
    add_edge(node2, node3);
    
    printf("Expected traversal output: ");
    graph_traversal(graph);
    printf("\n");
    
    destroy(graph);
    printf(" Graph traversal test completed\n");
}

int main() {
    printf("Running graph data structure tests...\n\n");
    
    test_create_node();
    test_create_graph();
    test_add_node_to_graph();
    test_add_edge();
    test_duplicate_edge();
    test_self_loop();
    test_check_visited();
    test_remove_edge();
    test_complete_graph();
    test_graph_traversal();
    test_graph_traversal_bfs();
    test_dfs_vs_bfs_comparison();
    
    printf("\n<� All tests passed!\n");
    return 0;
}

// Test BFS traversal  
void test_graph_traversal_bfs() {
    printf("Testing BFS graph traversal...\n");
    
    Graph* graph = create_graph();
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    Node* node4 = create_node(4);
    Node* node5 = create_node(5);
    Node* node6 = create_node(6);
    
    add_node_to_graph(node1, graph);
    add_node_to_graph(node2, graph);
    add_node_to_graph(node3, graph);
    add_node_to_graph(node4, graph);
    add_node_to_graph(node5, graph);
    add_node_to_graph(node6, graph);
    
    // Create a graph structure:
    // 1 - 2 - 3
    // |       |
    // 4 - 5 - 6
    add_edge(node1, node2);
    add_edge(node2, node3);
    add_edge(node1, node4);
    add_edge(node4, node5);
    add_edge(node5, node6);
    add_edge(node3, node6);
    
    printf("BFS traversal output: ");
    graph_traversal_bfs(graph);
    printf("\n");
    
    destroy(graph);
    printf(" BFS traversal test completed\n");
}

// Test comparing DFS vs BFS on same graph
void test_dfs_vs_bfs_comparison() {
    printf("Testing DFS vs BFS comparison...\n");
    
    Graph* graph = create_graph();
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    Node* node4 = create_node(4);
    
    add_node_to_graph(node1, graph);
    add_node_to_graph(node2, graph);
    add_node_to_graph(node3, graph);
    add_node_to_graph(node4, graph);
    
    // Simple chain: 1 - 2 - 3 - 4
    add_edge(node1, node2);
    add_edge(node2, node3);
    add_edge(node3, node4);
    
    printf("DFS output: ");
    graph_traversal(graph);
    printf("\n");
    
    printf("BFS output: ");
    graph_traversal_bfs(graph);
    printf("\n");
    
    destroy(graph);
    printf(" DFS vs BFS comparison test completed\n");
}