# Graphs

A graph is a non-linear data structure consisting of vertices (nodes) and edges that connect pairs of vertices. This implementation provides an adjacency list representation supporting both directed and undirected graphs with comprehensive traversal algorithms.

## Data Structure Overview

Graphs are versatile data structures that model relationships between objects:
- **Vertices (Nodes)**: Represent entities or data points
- **Edges**: Represent connections or relationships between vertices
- **Adjacency List**: Each node maintains a list of its connected neighbors

This implementation uses dynamic adjacency lists that resize automatically as connections are added.

## Graph Structure

```c
typedef struct Node {
    int num_connected;   // Number of current connections
    int adj_length;      // Current capacity of adjacency list
    int val;             // Node value/identifier
    struct Node** adj_list; // Dynamic array of connected nodes
} Node;

typedef struct Graph {
    int num_nodes;       // Current number of nodes
    int max_size;        // Current capacity
    struct Node** nodes; // Dynamic array of node pointers
} Graph;
```

## Time Complexity

| Operation | Adjacency List | Description |
|-----------|----------------|-------------|
| Add Vertex | O(1) amortized | Add node to graph |
| Add Edge | O(1) amortized | Connect two vertices |
| Remove Vertex | O(V + E) | Remove vertex and all edges |
| Remove Edge | O(V) | Remove connection between vertices |
| DFS Traversal | O(V + E) | Visit all reachable vertices |
| BFS Traversal | O(V + E) | Level-order traversal |
| Check Edge | O(V) | Verify connection exists |

Where V = number of vertices, E = number of edges

## Space Complexity
- **Adjacency List**: O(V + E) - Most space-efficient for sparse graphs
- **Memory per Node**: O(degree) - Only stores actual connections

## Core Functions

### Memory Management
- `create_node(int val)` - Creates a new node with given value
- `clear_node(Node* node)` - Frees node's adjacency list
- `create_graph()` - Creates an empty graph
- `destroy(Graph* graph)` - Frees entire graph structure

### Graph Operations
- `add_node_to_graph(Node* node, Graph* graph)` - Adds node to graph
- `remove_node(Node* node, Graph* graph)` - Removes node and all its edges

### Edge Operations
- `add_edge(Node* a, Node* b)` - Creates connection between two nodes
- `remove_edges(Node* node_a, Node* node_b)` - Removes connection
- `check_dupe(Node* a, Node* b)` - Checks if edge already exists

### Traversal Algorithms
- `graph_traversal(Graph* graph)` - DFS traversal of entire graph
- `graph_traversal_bfs(Graph* graph)` - BFS traversal of entire graph
- `run_dfs(Node* current, Node** visited, int* visited_count)` - DFS from specific node
- `check_visited(Node* current, Node** visited, int visited_length)` - Helper for traversal

## Usage Examples

### Creating and Building a Graph

```c
#include "graphs.h"
#include <stdio.h>

int main() {
    // Create graph and nodes
    Graph* graph = create_graph();
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    Node* node4 = create_node(4);
    
    // Add nodes to graph
    add_node_to_graph(node1, graph);
    add_node_to_graph(node2, graph);
    add_node_to_graph(node3, graph);
    add_node_to_graph(node4, graph);
    
    // Create edges (undirected graph)
    add_edge(node1, node2);  // 1 -- 2
    add_edge(node2, node3);  // 2 -- 3
    add_edge(node3, node4);  // 3 -- 4
    add_edge(node1, node4);  // 1 -- 4
    
    printf("Graph has %d nodes\n", graph->num_nodes);
    
    // Clean up
    destroy(graph);
    return 0;
}
```

### Graph Traversal Examples

```c
void traversal_example(Graph* graph) {
    printf("DFS Traversal: ");
    graph_traversal(graph);      // Depth-First Search
    printf("\n");
    
    printf("BFS Traversal: ");
    graph_traversal_bfs(graph);  // Breadth-First Search
    printf("\n");
}

// Example output for connected graph:
// DFS: 1 2 3 4 (order may vary based on adjacency list order)
// BFS: 1 2 4 3 (visits by levels/distance from start)
```

### Directed vs Undirected Graphs

```c
// Undirected graph - add edge in both directions
void create_undirected_edge(Node* a, Node* b) {
    add_edge(a, b);  // a -> b
    add_edge(b, a);  // b -> a
}

// Directed graph - add edge in one direction only
void create_directed_edge(Node* from, Node* to) {
    add_edge(from, to);  // from -> to only
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_graphs test_graphs.c graphs.c
```

Run the tests:
```bash
./test_graphs
```

## Graph Types Supported

### 1. Undirected Graphs
- Edges work in both directions
- If A connects to B, then B connects to A
- Used for: Social networks, road maps, peer connections

### 2. Directed Graphs (Digraphs)
- Edges have direction (one-way)
- A -> B doesn't imply B -> A
- Used for: Web pages, dependency graphs, state machines

### 3. Weighted Graphs
- Can be extended to include edge weights
- Current implementation focuses on unweighted graphs

## Traversal Algorithms

### Depth-First Search (DFS)
- Explores as far as possible along each branch
- Uses recursion (implicit stack)
- Good for: Pathfinding, cycle detection, topological sorting

### Breadth-First Search (BFS)
- Explores all neighbors at current depth before going deeper
- Uses queue data structure
- Good for: Shortest path (unweighted), level-order processing

## Applications

Graphs are fundamental in many domains:

### Computer Science
- **Web Crawling**: Pages as nodes, links as edges
- **Social Networks**: Users as nodes, friendships as edges
- **Dependency Resolution**: Packages/modules and their dependencies
- **Compiler Design**: Control flow graphs, call graphs

### Real World
- **Transportation**: Cities as nodes, routes as edges
- **Communication**: Devices as nodes, connections as edges
- **Biology**: Protein interactions, neural networks
- **Economics**: Market relationships, trade networks

## Graph Properties

### Connectivity
- **Connected**: Path exists between any two vertices
- **Disconnected**: Some vertices unreachable from others
- **Strongly Connected (Directed)**: Path exists in both directions

### Special Graph Types
- **Tree**: Connected acyclic graph with V-1 edges
- **Complete Graph**: Every vertex connected to every other vertex
- **Bipartite**: Vertices can be divided into two disjoint sets

## Advantages of Adjacency List

1. **Space Efficient**: Only stores existing edges
2. **Dynamic**: Easy to add/remove vertices and edges
3. **Fast Iteration**: Quick to iterate through neighbors
4. **Sparse Graph Friendly**: Optimal for graphs with few edges

## Disadvantages

1. **Edge Lookup**: O(V) time to check if specific edge exists
2. **Memory Overhead**: Pointer storage for each connection
3. **Cache Performance**: Less cache-friendly than adjacency matrix

## Memory Management Notes

- Graph automatically resizes when capacity is exceeded
- All adjacency lists are dynamically allocated
- Use `destroy()` to prevent memory leaks
- Nodes maintain their own memory for adjacency lists
- Removing a node automatically removes all its edges