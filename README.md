# Dragon Airline Management System

Dragon Airline is a console-based program written in C that simulates a network of airports and flight routes. The system allows users to build and manage towns (airports), define flight connections, and compute the most efficient travel routes based on time and cost. This project was developed as the final project of 2nd-semester **Data Structure** course.

---

## Program Overview

The system models airports as **nodes in a weighted graph** and flight routes as **directed edges** with two attributes:
- Travel cost
- Travel duration

Users interact with the program through a menu-based interface to manage towns and calculate routes.

---

## Features

### ➤ Add New Towns and Routes  
Users can create one or more towns, then define flight connections between them. Each route requires a cost and travel time. By default, connections are one-way, and a second entry is needed to create a two-way route.

### ➤ View All Towns and Flight Routes  
Displays every registered airport along with its outgoing routes, including cost and duration.

### ➤ Update Towns or Routes  
Users may:
- rename an existing town (with uniqueness validation), or  
- add or modify routes between towns  

Input validation is applied to keep the network consistent.

### ➤ Delete a Town  
Removes a town and automatically deletes all related routes.

### ➤ Calculate the Optimal Flight Route  
Given a starting town and a destination, the program computes:
- the **cheapest route**, and  
- the **fastest route**

using **BFS traversal and Dijkstra’s algorithm on a weighted graph**.  
If no valid path exists, the program notifies the user.

### ➤ Exit Program  
Closes the application.

---

## Concepts Implemented

This project applies key data structure and algorithm principles, including:

- Graph representation  
- Weighted edges  
- BFS (Breadth-First Search)  
- Dijkstra’s Algorithm  
- Struct-based data storage  
- Modular function design  
- Menu-driven interface  
- Input validation  

---

## Contributor

Anabelle Gabriella Imandjaja | Computer Science Student at BINUS University

Eldwin Sianto | Computer Science Student at BINUS University

Eduardo Garvey Wijaya | Computer Science Student at BINUS University
