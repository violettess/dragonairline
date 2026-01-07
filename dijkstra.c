#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>

#include "structs.h"
#include "dijkstra.h"
#include "graph.h"
#include "utility.h"

// Return the index of the nearest unvisited town
int minDistance(double distances[], bool visited[], int numTowns) {
    double min = DBL_MAX;
    int min_index = -1;
    
    // Go through all towns
    for (int v = 0; v < numTowns; v++) {
        if (!visited[v] && distances[v] < min) {
            min = distances[v]; // Update the smallest distance
            min_index = v;      // Update the index of the town
        }
    }
    
    return min_index;
}

// Utilize Dijkstra's algorithm to find shortest path
PathResult dijkstra(Graph* graph, int source, PathCriteria criteria) {
    PathResult result;
    bool visited[MAX_TOWNS];
    
    // Initialize distances and visited arrays
    for (int i = 0; i < graph->numTowns; i++) {
        result.distances[i] = DBL_MAX;  // Initialize all distances to infinity
        result.previous[i] = -1;        // Initialize index of previous
        visited[i] = false;             // Initialize all towns as unvisited
    }
    
    // Initialize distance of source vertex to itself as 0
    result.distances[source] = 0.0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < graph->numTowns - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(result.distances, visited, graph->numTowns);
        
        // If no reachable vertex is found
        if (u == -1) break;
        
        // Mark the picked vertex as processed
        visited[u] = true;
        
        // Update distances of the adjacent vertices
        Edge* edge = graph->adjacencyList[u];
        while (edge != NULL) {
            int v = edge->destination;
            double weight = (criteria == BY_COST) ? edge->costs : edge->hours;
            
            if (!visited[v] && result.distances[u] != DBL_MAX &&
                result.distances[u] + weight < result.distances[v]) {
                result.distances[v] = result.distances[u] + weight;
                result.previous[v] = u;
            }
            
            edge = edge->next;
        }
    }
    
    return result;
}

// Reconstructs the path from source to destination
void getPath(int destination, const int previous[], int path[], int* path_length) {
    *path_length = 0;
    
    int current = destination;
    while (current != -1) {
        path[(*path_length)++] = current;
        current = previous[current];
    }
}

// Find the cheapest path from source to destination
PathResult findCheapestPath(Graph* graph, int source) {
    return dijkstra(graph, source, BY_COST); // Call dijkstra by cost
}

// Find the fastest path from source to destination
PathResult findFastestPath(Graph* graph, int source) {
    return dijkstra(graph, source, BY_TIME); // Call dijkstra by time
}

// Check if a path exists between source and destination
bool pathExists(PathResult result, int destination) {
    return result.distances[destination] != DBL_MAX; // If the distance is still DBL_MAX, there was no path found.
}

// Return the total cost from the source to destination if PathResult is obtained with BY_COST
double getTotalCost(PathResult result, int destination) {
    return result.distances[destination];
}

// Return the total time from the source to destination if PathResult is obtained with BY_TIME
double getTotalTime(PathResult result, int destination) {
    return result.distances[destination];
}

// Print the shortest cost path from source to destination
void printCheapestPath(Graph* graph, int source, int destination) {
    PathResult result = findCheapestPath(graph, source);
    
    if (!pathExists(result, destination)) {
        printf("There is no flight route from %s to %s.\n", 
               graph->towns[source].name, 
               graph->towns[destination].name);
        return;
    }
    
    // Array to store the path
    int path[MAX_TOWNS];
    int path_length = 0;
    getPath(destination, result.previous, path, &path_length);
    
    // Print the path from source to destination
    printf("\nFlight route with the lowest cost from %s to %s:\n", 
           graph->towns[source].name, 
           graph->towns[destination].name);
    
    printf("Route: ");
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%s", graph->towns[path[i]].name);
        if (i > 0) printf(" -> ");
    }
    
    printf("\nTotal cost: IDR %.2lf K\n", getTotalCost(result, destination));
}

// Print the shortest time path from source to destination
void printFastestPath(Graph* graph, int source, int destination) {
    PathResult result = findFastestPath(graph, source);
    
    if (!pathExists(result, destination)) {
        printf("There is no route from %s to %s.\n", 
               graph->towns[source].name, 
               graph->towns[destination].name);
        return;
    }
    
    // Array to store the path
    int path[MAX_TOWNS];
    int path_length = 0;
    getPath(destination, result.previous, path, &path_length);
    
    // Print the path from source to destination
    printf("\nFlight route with the fastest time from %s to %s:\n", 
           graph->towns[source].name, 
           graph->towns[destination].name);
    
    printf("Route: ");
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%s", graph->towns[path[i]].name);
        if (i > 0) printf(" -> ");
    }
    
    printf("\nTotal time: %.2lf hours\n", getTotalTime(result, destination));
}

// Find and display shortest cost and shortest time paths
void findShortestPaths(Graph* graph, int source, int destination) {
	system("cls");
    
    if (source < 0 || source >= graph->numTowns || 
        destination < 0 || destination >= graph->numTowns) {
        printf("Invalid index.\n");
        return;
    }

    puts("======================================================");
    puts("|                 SHORTEST PATH ROUTE                |");
    puts("======================================================");

    PathResult result = findFastestPath(graph, source);
    
    if (!pathExists(result, destination)) {
        printf("There is no route from %s to %s.\n", 
               graph->towns[source].name, 
               graph->towns[destination].name);
        return;
    }

    // Find and print cheapest path
    printCheapestPath(graph, source, destination);
    
    // Find and print fastest path
    printFastestPath(graph, source, destination);
}

/* ----------------------- MAIN MENU FUNCTIONS (5) ----------------------- */

void shortestPathMenu(Graph* graph) {
    if(graph->numTowns < 2){
        system("cls");
        puts("======================================================");
        puts("|              FIND THE SHORTEST FLIGHT              |");
        puts("======================================================");
    	puts("Not enough towns to have routes (min. 2).");
    	printf("\nPress Enter to continue...");
        clearBuffer();
    	return;
	}

	char again ='y';
    while (again) {
        system("cls");
        puts("======================================================");
        puts("|              FIND THE SHORTEST FLIGHT              |");
        puts("======================================================");
        printAdjacencyList(graph);
        int source, destination;
        
        // Get source town
        puts("Input -1 to return.\n");
        source = getValidInt("Choose your departure", 1, graph->numTowns);
        if (source == -1) return;

        // Get destination town
        while(1) {
            destination = getValidInt("Choose your destination", 1, graph->numTowns);
            if(source == destination) {
                puts("Departure and destination cities cannot be the same.");
                continue;
            } else {
                break;
            }
        }
        
        // Find and display shortest paths
        findShortestPaths(graph, source-1, destination-1);
        again = getYesNoResponse("View other flight routes?");
    }
}
