#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structs.h"
#include "graph.h"
#include "utility.h"

Edge* createEdge(int dest, double cost, double hours) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newEdge->destination = dest;
    newEdge->costs = cost;
    newEdge->hours = hours;
    newEdge->next = NULL; //make sures newedge is not connected to anything
    return newEdge; // return the pointer to the newly created Edge structure

}

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    graph->numTowns = 0;
    for (int i = 0; i < MAX_TOWNS; i++) {
        graph->adjacencyList[i] = NULL; //making sure there's no edge on the newly created graph
    }
    return graph; 
}

//create a new town
void addTown(Graph* graph, const char* name) {
	//check if the number towns to add will exceeds maximum town number
    if (graph->numTowns >= MAX_TOWNS) {
        printf("Cannot add more towns.\n");
        return;
    }
    int id = graph->numTowns;
    strcpy(graph->towns[id].name, name);
    graph->numTowns++;
}

// checks if a path already exists between two towns
int isPathExists(Graph* graph, int source, int destination) {
    if (source < 0 || destination < 0 || source >= graph->numTowns || destination >= graph->numTowns) {
        return 0;
    }

    Edge* current = graph->adjacencyList[source];
    while (current) {
        if (current->destination == destination) {
            return 1; //path found
        }
        current = current->next; //move to the next edge
    }

    return 0;  // no direct path found

}

// adds a unique path if it does not already exist
void addPath(Graph* graph, int source, int destination, double cost, double hours) {
    if (source < 0 || destination < 0 || source >= graph->numTowns || destination >= graph->numTowns) {
        printf("Invalid town indices!\n");
        return;
    }
	
	// check if a path from source to destination already exists
    if (isPathExists(graph, source, destination)) {
        printf("Path already exists from %s to %s.\n", graph->towns[source].name, graph->towns[destination].name);
        return;
    }

    Edge* newEdge = createEdge(destination, cost, hours); // create a new edge representing the path
    newEdge->next = graph->adjacencyList[source]; // insert the new edge at the beginning of the adjacency list for the source town
    graph->adjacencyList[source] = newEdge;
}

//release all of the existing town
void freeGraph(Graph* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->numTowns; i++) {
        Edge* current = graph->adjacencyList[i];
        while (current) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}

//see all available flight routes
void printGraph(Graph* graph) {
	puts("======================================================");
    puts("|              Available Flight Routes               |");
    puts("======================================================");
    for (int i = 0; i < graph->numTowns; i++) {
        printf("%02d. Town %s:\n", i+1, graph->towns[i].name);
        Edge* edge = graph->adjacencyList[i]; //check edge in a town
        if (!edge) {
            printf("  No connection.\n");
        }
        while (edge) {
            printf("  -> %s | Cost: %.2lf | Hours: %.2lf\n",
                   graph->towns[edge->destination].name,
                   edge->costs, edge->hours);
            edge = edge->next;
        }
    	puts("======================================================");
        printf("\n");
    }
}

//print routes in adjacencylist
void printAdjacencyList(Graph* graph) {

    puts(" Adjacency List");
    for (int i = 0; i < graph->numTowns; i++) {
        printf("%d. [%s]", i + 1, graph->towns[i].name);
        Edge* edge = graph->adjacencyList[i];
        while (edge) {
            printf(" -> %s", graph->towns[edge->destination].name);
            edge = edge->next;
        }
        printf("\n");       
    }
        puts("======================================================");


    printf("\n");
}

//check all exist path from departure town to destination town
void printAllPathsUtil(Graph* graph, int current, int destination, bool visited[], int path[], int pathIndex, bool* found) {
    visited[current] = true;
    path[pathIndex++] = current;

    if (current == destination) {
        *found = true; // set found = true jika ada jalur sampai tujuan
        for (int i = 0; i < pathIndex; i++) {
            printf("%s", graph->towns[path[i]].name);
            if (i < pathIndex - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        Edge* edge = graph->adjacencyList[current];
        while (edge) {
            if (!visited[edge->destination]) {
                printAllPathsUtil(graph, edge->destination, destination, visited, path, pathIndex, found);
            }
            edge = edge->next;
        }
    }

    visited[current] = false;
}

//print all exist path from departure town to destination town
void printAllPaths(Graph* graph, int source, int destination) {
    bool visited[MAX_TOWNS] = {false};
    int path[MAX_TOWNS];
    int pathIndex = 0;
    bool found = false;
	printAllPathsUtil(graph, source, destination, visited, path, pathIndex, &found);
    if (!found) {
        printf("No flight route from %s to %s.\n", graph->towns[source].name, graph->towns[destination].name);
    }
}

//check if name is unique name
bool townExists(Graph* graph, const char* name) {
    for (int i = 0; i < graph->numTowns; i++) {
        if (strcmp(graph->towns[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

//count every edge to make sure if all town already connected
int countEdges(Graph* graph) {
    int count = 0;
    for (int i = 0; i < graph->numTowns; i++) {
        Edge* curr = graph->adjacencyList[i];  
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }
    }
    return count;
}

/* ----------------------- MAIN MENU FUNCTIONS (1) ----------------------- */
void addTowns(Graph* graph) {
    system("cls");
    puts("======================================================");
    puts("|                   ADD NEW TOWNS                    |");
    puts("======================================================");

    puts("Input -1 to return.\n");
    int townAdd = getValidInt("Number of towns to add", 1, 100 - graph->numTowns); 
    if (townAdd == -1) return;
    
    for (int i = 0; i < townAdd; i++) {
        char name[MAX_NAME_LENGTH];
        char prompt[50];
        snprintf(prompt, sizeof(prompt), "Town #%02d [max 49 char]: ", i + 1);
        
        do {
            getValidString(prompt, name, MAX_NAME_LENGTH); //input town name
            capitalFirstLetter(name);
            if (townExists(graph, name)) {
                printf("Town %s already exist\n", name); 
            }
        } while (townExists(graph, name));
        
        addTown(graph, name); // Just add the town
    }
    puts("======================================================");
    printf("Towns added!\n");
    puts("\nPress Enter to continue...");
    clearBuffer();
}

/* ----------------------- MAIN MENU FUNCTIONS (2) ----------------------- */

//connect departure town to destination town
void connectTowns(Graph* graph) {
    system("cls");

    if(graph->numTowns < 2) {  
        puts("======================================================");
        puts("|               ADD NEW FLIGHT ROUTES                |");
        puts("======================================================");
        printAdjacencyList(graph);
        puts("Not enough towns to connect (min. 2).");
        printf("\nPress Enter To continue...");
        clearBuffer();
        return;
    }
    
    int maxEdges = graph->numTowns * (graph->numTowns - 1); //Maximal edges could exist
    int again = 1;
    while (again) {
        system("cls");
        puts("======================================================");
        puts("|               ADD NEW FLIGHT ROUTES                |");
        puts("======================================================");
        
        if (countEdges(graph) == maxEdges) {
            puts("All towns are already fully connected.");
            printf("\nPress Enter To continue...");
            clearBuffer();
            return;
        }
        printAdjacencyList(graph);
        
        puts("Input -1 to return.\n");
        int source = getValidInt("Choose departure town", 1, graph->numTowns);
        if (source == -1) return;
        source--;
        
        int destination;
        int duplicate = 0;
        do {
            destination = getValidInt("Connect with destination town", 1, graph->numTowns) - 1;
            if (source == destination) {
                printf("Departure and destination towns must not be the same\n");
            }

            duplicate = isPathExists(graph, source, destination); // check if path already exist
            if (duplicate) {
                printf("Path already exists from %s to %s.\n", graph->towns[source].name, graph->towns[destination].name);
                break;
            }
        } while (source == destination || duplicate);
        
        if (!duplicate) { //insert weight in edge if path yet exist
            double hours = getValidDouble("Flight length (hours)", 0.01, 48);
            double cost = getValidDouble("Flight cost (in 1k IDR)", 100, 100000);
            addPath(graph, source, destination, cost, hours); 
        }
        
        again = getYesNoResponse("Do you want to add another connection?");
    }
}
/* ----------------------- MAIN MENU FUNCTIONS (3) ----------------------- */

void showRoute(Graph* graph) {
    system("cls");
    puts("======================================================");
    puts("|              SHOWING ALL FLIGHT ROUTES             |");

    if(graph->numTowns < 2) {  // Use graph->numTowns directly
        puts("======================================================");
        printAdjacencyList(graph);
        puts("Not enough towns to show routes (min. 2)."); 
    } else {
        printGraph(graph);

        puts("Input -1 to return.\n");
        int source = getValidInt("Choose departure town", 1, graph->numTowns);
        if (source == -1) return;
        source--;

        int destination;
        do {
            destination = getValidInt("Choose destination town", 1, graph->numTowns) - 1;
            if (source == destination) {
                printf("Departure and destination towns must not be the same\n");
            } else {
                system("cls");
                puts("======================================================");
                puts("|             AVAILABLE FLIGHT ROUTES                |");
                puts("======================================================");
                printAllPaths(graph, source, destination);
            }
        } while(destination == source);
    }
    
    printf("\nPress Enter to continue...");
    clearBuffer();
    return;
}





