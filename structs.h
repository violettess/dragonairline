#ifndef STRUCTS_H
#define STRUCTS_H

// Max number of towns (nodes) that can be in the graph
#define MAX_TOWNS 100

// Max length for the name of a town
#define MAX_NAME_LENGTH 50

// Town structure (node)
typedef struct Town {
    char name[MAX_NAME_LENGTH]; // Name of the town
} Town;

// Route structure (edge)
typedef struct Edge {
    int destination;        // Index of the destination town in the graph's towns array
    double costs;           // Cost to travel this edge (e.g., money or ticket price)
    double hours;           // Time to travel this edge (e.g., in hours)
    struct Edge* next;      // Pointer to the next edge (linked list for adjacency list)
} Edge;

// Graph representation using adjacency list
typedef struct Graph {
    int numTowns;                       // Current number of towns in the graph
    Town towns[MAX_TOWNS];              // Array of all town structures
    Edge* adjacencyList[MAX_TOWNS];     // Array of all edges (adjacency list representation)
} Graph;

// Stores the results of shortest path calculation (for Dijkstra’s algorithm)
typedef struct PathResult {
    double distances[MAX_TOWNS];    // Shortest distance (or cost/time) from source to each town
    int previous[MAX_TOWNS];        // Stores previous node in path (used for path reconstruction)
} PathResult;

// Enum to define whether to calculate shortest path by cost or by time
typedef enum {
    BY_COST,
    BY_TIME
} PathCriteria;

#endif
