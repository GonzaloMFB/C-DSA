#ifndef GRAPHS_H
#define GRAPHS_H

typedef struct Node {
    int num_connected;
    int adj_length;
    int val;
    struct Node** adj_list;
} Node;

typedef struct Graph {
    int num_nodes;
    int max_size;
    struct Node** nodes;
} Graph;

// Node operations
Node* create_node(int val);
void clear_node(Node* node);

// Graph operations
Graph* create_graph();
void destroy(Graph* graph);
void add_node_to_graph(Node* node, Graph* graph);
void remove_node(Node* node, Graph* graph);

// Edge operations
void add_edge(Node* a, Node* b);
void remove_edges(Node* node_a, Node* node_b);
int check_dupe(Node* a, Node* b);

// Traversal operations
void graph_traversal(Graph* graph);
void graph_traversal_bfs(Graph* graph);
void run_dfs(Node* current, Node** visited, int* visited_count);
int check_visited(Node* current, Node** visited, int visited_length);

// Internal utility functions
void resize_adj_list(Node* node);
void resize(Graph* graph);

#endif