#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdbool.h>
#include "structs.h"
#include "graph.h"

// Return the index of the nearest unvisited town
int minDistance(double distances[], bool visited[], int numTowns);

// Dijkstra algorithm to find shortest path
PathResult dijkstra(Graph* graph, int source, PathCriteria criteria);

// Reconstruct path
void getPath(int destination, const int previous[], int path[], int* path_length);

// Function wrappers for cost and time
PathResult findCheapestPath(Graph* graph, int source);
PathResult findFastestPath(Graph* graph, int source);

// Function wrapper for path check and evaluation
bool pathExists(PathResult result, int destination);
double getTotalCost(PathResult result, int destination);
double getTotalTime(PathResult result, int destination);

// Display paths
void printCheapestPath(Graph* graph, int source, int destination);
void printFastestPath(Graph* graph, int source, int destination);
void findShortestPaths(Graph* graph, int source, int destination);

// Menu
void shortestPathMenu(Graph* graph);

#endif
