#ifndef GRAPH_H
#define GRAPH_H

#include "structs.h"

// Graph 
Graph* createGraph();
Edge* createEdge(int dest, double cost, double hours);
void addTown(Graph* graph, const char* name);
void addPath(Graph* graph, int source, int destination, double cost, double hours);
void freeGraph(Graph* graph);

// Town 
bool townExists(Graph* graph, const char* name);
int isPathExists(Graph* graph, int source, int destination);
int countEdges(Graph* graph);

// Print functions
void printGraph(Graph* graph);
void printAdjacencyList(Graph* graph);
void printAllPaths(Graph* graph, int source, int destination);
void printAllPathsUtil(Graph* graph, int current, int destination, bool visited[], int path[], int pathIndex, bool* found);

// Main menu functions
void addTowns(Graph* graph);
void connectTowns(Graph* graph);
void showRoute(Graph* graph);

#endif
