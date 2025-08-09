#include <stdio.h>
#include <stdlib.h>

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

// Function declarations
int check_visited(Node* current, Node** visited, int visited_length);
void remove_edge(Node* deleted_node, Node* node);

Node* create_node(int val) {
    // Naive case, let's make it 8 connections max at the start.
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "MALLOC FAILURE - Could not allocate %lu bytes.\n", sizeof(Node));
        return NULL;
    }
    node->num_connected = 0;
    node->val = val;
    node->adj_length = 8;
    Node** adj_list = malloc(node->adj_length * sizeof(Node*));
    if (adj_list == NULL) {
        free(node);
        fprintf(stderr, "MALLOC FAILURE - Could not allocate %lu bytes.\n", 8 * sizeof(Node*));
        return NULL;
    }
    node->adj_list = adj_list;
    return node;

}

Graph* create_graph() {
    Graph* graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "MALLOC FAILURE - Could not allocate %lu bytes.\n", sizeof(Graph));
        return NULL;
    }
    graph->num_nodes = 0;
    int max_size = 8;
    Node** node_list = malloc(max_size*sizeof(Node*));
    if (node_list == NULL) {
        free(graph);
        fprintf(stderr, "MALLOC FAILURE - Could not allocate %lu bytes.\n", 8 * sizeof(Node*));
        return NULL;
    }
    graph->max_size = max_size;
    graph->nodes = node_list;
    return graph;
}

void resize_adj_list(Node* node) {
    // Resizes the adjacency list to double its original length.
    node->adj_length = node->adj_length * 2;
    Node** adj_list = malloc(node->adj_length * sizeof(Node*));
    if (adj_list == NULL) {
        fprintf(stderr, "MALLOC FAILURE - Could not allocate %lu bytes.\n", node->adj_length * sizeof(Node*));
        return;
    }
    for (int i = 0; i < node->num_connected; i++) {
        adj_list[i] = node->adj_list[i];
    }
    free(node->adj_list);
    node->adj_list = adj_list;
}

int check_dupe(Node* a, Node* b) {
    for (int i = 0; i < b->num_connected; i++) {
        if (a == b->adj_list[i])   return 1; 
    }
    return 0;
}

void clear_node(Node* node) {
    // We need to free the adjacent list and the node itself.
    // First, free the adjacency list. You do not destroy the nodes inside.
    if (node == NULL) return;
    free(node->adj_list);
    node->adj_list = NULL;
    free(node);
    node = NULL;
}

void destroy(Graph* graph) {
    if (graph == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Graph*\n");
    }
    for (int i = 0; i < graph->num_nodes; i++) {
        // We free everything in the node.
        clear_node(graph->nodes[i]);
    }
    free(graph);
    graph = NULL; // dangling pointer.
}

void add_edge(Node* a, Node* b) {
    if (a == NULL || b == NULL) {
        fprintf(stderr, "ERROR - Make sure to pass proper Node* for both a and b.\n");
        return;
    }
    if (a == b) {
        printf("Trying to add an edge between the same node (A <-> A). No action taken.\n");
        return;
    }
    // Check if edge already exists
    int dupe_ab = check_dupe(a, b); 
    int dupe_ba = check_dupe(b, a);
    
    // Add b to a's adjacency list if not already there
    if (dupe_ba != 1) {
        a->adj_list[a->num_connected] = b;
        (a->num_connected)++;
        if (a->num_connected >= 0.7 * a->adj_length) {
            resize_adj_list(a);
        }
    }
    
    // Add a to b's adjacency list if not already there
    if (dupe_ab != 1) {
        b->adj_list[b->num_connected] = a;
        (b->num_connected)++;
        if (b->num_connected >= 0.7 * b->adj_length) {
            resize_adj_list(b);
        }    
    }
}

void resize(Graph* graph) {
    graph->max_size *= 2;
    Node** new_list = malloc(graph->max_size * sizeof(Node*));
    if (new_list == NULL) {
        fprintf(stderr, "MALLOC FAILURE - Could not allocate %lu bytes.\n", graph->max_size * sizeof(Node*));
        return;
    }
    for (int i = 0; i < graph->num_nodes; i++) {
        new_list[i] = graph->nodes[i];
    }
    free(graph->nodes);
    graph->nodes = new_list;
}

void add_node_to_graph(Node* node, Graph* graph) {
    if (node == NULL || graph == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Node* and a valid Graph*.\n");
        return;
    }
    graph->nodes[graph->num_nodes] = node;
    (graph->num_nodes)++;
    if (graph->num_nodes > 0.7 * graph->max_size) {
        resize(graph);
    }
}

void remove_edges(Node* node_a, Node* node_b) {
    remove_edge(node_a, node_b);
    remove_edge(node_b, node_a);
}

void remove_edge(Node* deleted_node, Node* node) {
    // Internal func only.
    int idx = -1;
    for (int i = 0; i < node->num_connected; i++){
        if (node->adj_list[i] == deleted_node) {
            idx = i;
            break;
        }
    }
    // After finding the node, we swap it with the last node in the adj_list,
    // then decrement the count.
    if (idx != -1) {
        Node* tmp = node->adj_list[(node->num_connected)-1];
        node->adj_list[(node->num_connected)-1] = node->adj_list[idx];
        node->adj_list[idx] = tmp;
        (node->num_connected)--;
    }
    
}

void remove_node(Node* node, Graph* graph) {
    if (node == NULL || graph == NULL) {
        fprintf(stderr, "ERROR - Must pass a valid Node* and a valid Graph*.\n");
        return;
    }
    // Go through all nodes in the adjacency list and remove the edge.
    // Since they are in the adj list, we know they are connected, don't have to check.
    for (int i = 0; i < node->num_connected; i++) {
        remove_edge(node, node->adj_list[i]);
    }

    // Now we remove the node from the graph's list.
    int idx  =-1;
    for (int i = 0; i < graph->num_nodes; i++) {
        if (graph->nodes[i] == node) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        // Swap it with last element & reduce count for removing at index.
        // If we add a node, it'll overwrite the last element we just swapped, so it's ok.
        Node* tmp = graph->nodes[(graph->num_nodes)-1];
        graph->nodes[(graph->num_nodes)-1] = graph->nodes[idx];
        graph->nodes[idx] = tmp;
        (graph->num_nodes)--;
        clear_node(node);
    }
}

void run_dfs(Node* current, Node** visited, int* visited_count) {
    for (int i = 0; i < current->num_connected; i++) {
        // Now, we check if the node is in the visited list.
        if (check_visited(current, visited, *visited_count) == 0) {
            // Add to visited list and increase visited count.
            visited[*visited_count] = current;
            (*visited_count)++;
            printf("%d ", current->val);  // Action to take during traversal.
            run_dfs(current->adj_list[i], visited, visited_count);
        }
    }
}

int check_visited(Node* current, Node** visited, int visited_length) {
    // returns 0 if not in visited, 1 if it is.
    for (int i = 0; i < visited_length; i++) {
        if (current == visited[i]) return 1;
    }
    return 0;
}

void graph_traversal(Graph* graph) {
    Node* visited[graph->num_nodes]; // keep track of visited.
    int visited_count = 0;

    for (int i = 0; i < graph->num_nodes; i++) {
        if (check_visited(graph->nodes[i], visited, visited_count) == 0) {
            visited[visited_count] = graph->nodes[i];
            visited_count++;
            printf("%d ", graph->nodes[i]->val);
            run_dfs(graph->nodes[i], visited, &visited_count);
        }
    }
}

void graph_traversal_bfs(Graph* graph) {
    Node* visited[graph->num_nodes]; // keep track of visited.
    int visited_count = 0;
    Node* queue[graph->num_nodes]; // For BFS.
    int queued_count = 0;
    // For loop because a node may be disconnected from the rest.
    // So we can't just add a node to the queue and go from there.
    // This makes sure we check all of them.
    for (int i = 0; i < graph->num_nodes; i++) {
         if (check_visited(graph->nodes[i], visited, visited_count) == 0) {
            visited[visited_count] = graph->nodes[i];
            visited_count++;
            printf("%d ", graph->nodes[i]->val);
            // Add adjacent, non-visited nodes to the queue.
            for (int j = 0; j < graph->nodes[i]->num_connected; j++) {
                if (check_visited(graph->nodes[i]->adj_list[j], visited, visited_count) == 0) {
                    queue[queued_count] = graph->nodes[i]->adj_list[j];
                    queued_count++;
                    visited[visited_count] = graph->nodes[i]->adj_list[j];
                    visited_count++;
                }
                
            }
            while(queued_count > 0) {
                Node* current = queue[0];
                for (int j = 1; j < queued_count; j++) {
                    queue[j-1] = queue[j];
                }
                queued_count--;
                printf("%d ", current->val);
                // Add its adjacents
                for (int j = 0; j < current->num_connected; j++) {
                    if (check_visited(current->adj_list[j], visited, visited_count) == 0) {
                        queue[queued_count] = current->adj_list[j];
                        visited[visited_count] = current->adj_list[j];
                        visited_count++;
                        queued_count++;
                    }
                }
            }
         }
    }
}