#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "utility.h"
#include "structs.h"
#include "dijkstra.h"
#include "update.h"

int main() {
    system("cls");  
    splashScreen();
    
    Graph* graph = createGraph();
    
    int choice;
    
    while (1) {
        system("cls");
        choice = mainMenu();
        switch (choice) {
            case 1: // Menu 1: Add new towns
                addTowns(graph);
                break;
            case 2: // Menu 2: Add new connections
                connectTowns(graph);
                break;
            case 3: // Menu 3: View all towns and flight routes
                showRoute(graph);
                break;
            case 4: // Menu 4: Update existing towns and flight routes
                if (updateMenu(graph) == -1) {
                    continue;
                }
                break;
            case 5: // Menu 5: Delete towns and flight routes
                deleteTown(graph);
                break;
            case 6: // Menu 6: Compute the optimal flight route
                shortestPathMenu(graph);
                break;
            case 7: // Menu 7: Exit the program
                exitProgram(graph);
                break;
            default:
                break;
        }
        printf("\n");
    }
    return 0;
}