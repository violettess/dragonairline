#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "structs.h"
#include "dijkstra.h"
#include "graph.h"
#include "utility.h"

//function to delete route 
void deleteRoute(Graph* graph, int source, int destination) {
    Edge* current = graph->adjacencyList[source];//start at the head of the edge list for the source town
    Edge* prev = NULL;

    while (current != NULL) { //go through edge list
        if (current->destination == destination) {
            if (prev == NULL) { //delete if first in list
                graph->adjacencyList[source] = current->next; //update head
            } else {
                prev->next = current->next; //skip current
            }
            free(current);//free deleted
            printf("Route deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next; 
    }

    printf("Route not found.\n");
}

//function to update route
void updateRoutes(Graph* graph, int source) {
    int destination = -1;
    double newCost, newHours;
    int choice;
    system("cls");

    Edge* edge = graph->adjacencyList[source];//check if a town has any route
    if (!edge) {
        printf("No connections available to update for this town.\n");
        printf("Press Enter to continue...");
        clearBuffer();
        return;
    }

    int idx = 1;
    puts("======================================================");
    printf("Connections from %s:\n", graph->towns[source].name);
    puts("======================================================");
    for (Edge* temp = edge; temp; temp = temp->next) //loop to print all the route from a selected town
        printf("%d. To %s\n", idx++, graph->towns[temp->destination].name);
    puts("======================================================");
    puts("Input -1 to return.\n");
    int selection = getValidInt("Choose the connection to update", 1, idx - 1); //validate input for which route to update
    if (selection == -1) return;
    Edge* selectedEdge = edge;
    for (int i = 1; i < selection; i++) selectedEdge = selectedEdge->next;

    double oldCost = selectedEdge->costs;
    double oldHours = selectedEdge->hours;

    do {
        newCost = getValidDouble("Input the new price (in 1k IDR)", 100, 100000); //input a new price for the route
        if (newCost == oldCost) //check whether the price is the same as before
            printf("New price must be different from the old one (%.2f).\n", oldCost); //if price is the same, loop to ask for unique input
    } while (newCost == oldCost);

    do {
        newHours = getValidDouble("Input the new length of trip (hours)", 0.01, 48); //input a new length of trip for the route
        if (newHours == oldHours) //check whether the time is the same as before
            printf("New duration must be different from the old one (%.2f).\n", oldHours); //if time is the same, loop to ask for unique input
    } while (newHours == oldHours);

    selectedEdge->costs = newCost; //update the price
    selectedEdge->hours = newHours; //update the length of trip

    printf("Update success.\n");
    printf("Press Enter to continue...");
    clearBuffer();
}

void updateName(Graph* graph) {
    system("cls");
    puts("======================================================");
    puts("|                UPDATE TOWN NAME                    |");
    puts("======================================================");

    if (graph->numTowns == 0) { //check for the amount of town available. Minimum 1
        puts("No towns available to update.");
        printf("Press Enter to continue...");
        clearBuffer();
        return;
    }

    printAdjacencyList(graph);
    puts("Input -1 to return.\n");
    int index = getValidInt("Choose the town number to rename", 1, graph->numTowns); //ask user to input which town they want to rename
    if (index == -1) return;
    index -= 1;

    char newName[MAX_NAME_LENGTH];
    bool nameExists;

    do { //looping to check for a unique name input
        nameExists = false;
        char prompt[50];
        snprintf(prompt, sizeof(prompt), "Enter new name for [%s]: ", graph->towns[index].name); //ask user to input a new name
        getValidString(prompt, newName, MAX_NAME_LENGTH); 
        capitalFirstLetter(newName); //Makes the first letter always capital

        if (strcmp(graph->towns[index].name, newName) == 0) { //loop to check with the previous name
            printf("New name must be different from the old name.\n"); //ask user to input a new name if the inputted name is the same as previous
            nameExists = true; //name already exist
            continue;//loop to ask for input
        }

        for (int i = 0; i < graph->numTowns; i++) { //loop to check with the other towns' names
            if (i != index && strcmp(graph->towns[i].name, newName) == 0) {//compare all the town name with the new name
                printf("That name already exists. Please enter a unique town name.\n"); //ask user to input a new name if the inputted name is used by other town
                nameExists = true; //name already exist
                break; //loop
            }
        }
    } while (nameExists);

    strcpy(graph->towns[index].name, newName); //put the new name as the current name for that town

    puts("Town name updated successfully.\n");
    puts("Press Enter to continue...");
    clearBuffer();
}

/* ----------------------- MAIN MENU FUNCTIONS (4) ----------------------- */
int updateMenu(Graph* graph) {
    while (1) {
        system("cls");
        puts("======================================================");
        puts("|                   UPDATING MENU                    |");
        puts("======================================================");
        puts("| 1. Update town name                                |");
        puts("| 2. Update routes from a town                       |");
        puts("======================================================");
        puts("Input -1 to return.\n");

        int choice = getValidInt("Choice", 1, 2); 
        if (choice == -1) return -1;

        system("cls");

        switch (choice) {
            case 1:
                updateName(graph);
                break;
            case 2: {
                if (graph->numTowns < 2) {
                    puts("There are not enough towns to update (min. 2)");
                    puts("Press Enter to continue...");
                    clearBuffer();
                    return 0;
                }

                printAdjacencyList(graph);
                puts("Input -1 to return.\n");

                int source = getValidInt("Which town do you want to update", 1, graph->numTowns);
                if (source == -1) break;

                updateRoutes(graph, source - 1);
                break;
            }
            default:
                break;
        }
    }
    return 0;
}

//function to delete a route
void deleteRouteMenu(Graph* graph) {
    while (1) {
        system("cls");
        puts("======================================================");
        puts("|                  DELETE A ROUTE                    |");
        puts("======================================================");
        printAdjacencyList(graph);

        puts("Input -1 to return.\n");

        int from = getValidInt("Which town is the route you want to delete from", 1, graph->numTowns);//ask user to input a number for which route they want to delete
        if (from == -1) return;
        from -= 1;

        Edge* edge = graph->adjacencyList[from]; 
        if (!edge) { //check whether there are any routes or no
            puts("No outgoing routes from this town.");
            printf("Press Enter to continue...");
            clearBuffer();
            continue;
        }

        while (1) {
            system("cls");
            puts("======================================================");
            printf(" Showing routes from %s:\n", graph->towns[from].name);
            puts("======================================================");

            int idx = 1;
            int options[100];

            for (Edge* temp = edge; temp; temp = temp->next) { //print all route from the source town
                printf("%d. To %s\n", idx, graph->towns[temp->destination].name); //print number and destination
                options[idx - 1] = temp->destination; //store in option array
                idx++; //move to next option
            }

            puts("Input -1 to return.\n");
            int sel = getValidInt("Choose the route to delete", 1, idx - 1); //ask user to input a number for which route to delete
            if (sel == -1) break;

            int destination = options[sel - 1]; //-1 agar index
            deleteRoute(graph, from, destination);
            printf("Press Enter to continue...");
            clearBuffer();
            break;
        }
    }
}

//function to delete town
void deleteTownMenu(Graph* graph) {
    system("cls");
    puts("======================================================");
    puts("|                  DELETE A TOWN                     |");
    puts("======================================================");
    printAdjacencyList(graph);

    puts("Input -1 to return.\n");

    int townToDelete = getValidInt("Choose town to delete", 1, graph->numTowns); //ask user to input number for which town to delete
    if (townToDelete == -1) return;
    townToDelete -= 1;

    //Remove route going to that town
    for (int i = 0; i < graph->numTowns; i++) {
        if (i == townToDelete) continue; //skip town to be del
        Edge** edgePtr = &graph->adjacencyList[i];
        while (*edgePtr) {
            if ((*edgePtr)->destination == townToDelete) {
                Edge* toDelete = *edgePtr;
                *edgePtr = (*edgePtr)->next;
                free(toDelete);
            } else {
                if ((*edgePtr)->destination > townToDelete)
                    (*edgePtr)->destination--;
                edgePtr = &(*edgePtr)->next;
            }
        }
    }

    //Remove route going from that town
    while (graph->adjacencyList[townToDelete]) { //loop if there is edge
        Edge* temp = graph->adjacencyList[townToDelete]; //store edge
        graph->adjacencyList[townToDelete] = temp->next; //move head
        free(temp);
    }

    //move towns up to fill empty space
    for (int i = townToDelete; i < graph->numTowns - 1; i++) {
        graph->towns[i] = graph->towns[i + 1]; //shift town up
        graph->adjacencyList[i] = graph->adjacencyList[i + 1]; //shift adjecency list up
    }

    graph->adjacencyList[graph->numTowns - 1] = NULL; //set the last in list to null
    (graph->numTowns)--;
    
    puts("Town deleted successfully.");
    puts("Press Enter to continue...");
    clearBuffer();
}

/* ----------------------- MAIN MENU FUNCTIONS (5) ----------------------- */
void deleteTown(Graph* graph) {
    while (1) {
        system("cls");
        puts("======================================================");
        puts("|                   DELETE MENU                      |");
        puts("======================================================");

        if (graph->numTowns == 0) { //check the amount of town available
            puts("No towns to delete.");
            puts("Press Enter to continue...");
            clearBuffer();
            return;
        }

        puts("======================================================");
        puts("| What do you want to delete?                        |");
        puts("| 1. Town                                            |");
        puts("| 2. Flight route                                    |");
        puts("| Input -1 to return                                 |");
        puts("======================================================");

        int menuChoice = getValidInt("Choice", 1, 2); //ask user to input choice
        if (menuChoice == -1) return;

        switch (menuChoice) {
            case 1:
                deleteTownMenu(graph); //go to delete town function
                break;
            case 2:
                deleteRouteMenu(graph); //go to delete route function
                break;
            default:
                break;
        }
    }
}
