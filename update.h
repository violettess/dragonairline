#ifndef UPDATE_H
#define UPDATE_H

#include <stdbool.h>
#include "structs.h"
#include "dijkstra.h"
#include "graph.h"
#include "utility.h"

// Deletes a route from source to destination
void deleteRoute(Graph* graph, int source, int destination);

// Updates a route from a town (by index)
void updateRoutes(Graph* graph, int source);

// Rename a town
void updateName(Graph* graph);

// Main update menu
int updateMenu(Graph* graph);

// Menu to delete a specific route
void deleteRouteMenu(Graph* graph);

// Menu to delete a town
void deleteTownMenu(Graph* graph);

// Delete a town
void deleteTown(Graph* graph);

#endif
