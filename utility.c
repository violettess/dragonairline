#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "utility.h"
#include "graph.h"

/* ----------------------- MAIN MENU FUNCTIONS ----------------------- */

void splashScreen() {
    puts("=============================================");
    puts("|              DRAGON AIRLINE               |");
    puts("=============================================\n");

    puts("=============================================");
    puts("| Created by: Naga Udara                    |");
    puts("| 2802410213 - Anabelle Gabriella Imandjaja |");
    puts("| 2802434320 - Eldwin Sianto                |");
    puts("| 2802431256 - Eduardo Garvey Wijaya        |");
	puts("=============================================");
    printf("\nPress Enter to continue...");
    clearBuffer();
}

/* ----------------------- MAIN MENU FUNCTIONS ----------------------- */

int mainMenu() {
    puts("==============================================");
	puts("|         WELCOME TO DRAGON AIRLINE          |");
    puts("==============================================");
    puts("| 1. Add new towns                           |");
    puts("| 2. Add new connections                     |");
    puts("| 3. View all towns and flight routes        |");
    puts("| 4. Update existing towns and flight routes |");
    puts("| 5. Delete towns and flight routes          |");
    puts("| 6. Calculate the optimal flight route      |");
    puts("| 7. Exit the program                        |");
    puts("==============================================");
    return getValidInt("Choose", 1, 7);
}

/* ----------------------- MAIN MENU FUNCTIONS (6) ----------------------- */

void exitProgram(Graph *graph) {
    int answer;
    system("cls");

    puts("==============================================");
    puts("|               EXIT PROGRAM                 |");
    puts("==============================================\n");

    answer = getYesNoResponse("Do you want to exit the program?");
    printf("\n");

    if (answer == 1) { // 'y'
        freeGraph(graph);
        puts("Thank you for using our program!");
        puts("Exiting the program...");
        printf("\nPress Enter to continue...");
        clearBuffer();
        exit(0);
    } else { // 'n'
        puts("Returning to main menu...");
        printf("\nPress Enter to continue...");
        clearBuffer();
        return;
    }
}

/* ----------------------- UTIL FUNCTIONS ----------------------- */

// Function to clear the leftover characters in buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ----------------------- VALIDATION FUNCTIONS ----------------------- */

int getValidInt(const char* basePrompt, int min, int max) {
    int input;
    char buffer[100];
    char fullPrompt[150];
    
    snprintf(fullPrompt, sizeof(fullPrompt), "%s [%d - %d]: ", basePrompt, min, max); // Add the boundary to the prompt
    
    while (1) {
        printf("%s", fullPrompt);
        
        // Get input as string
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            clearBuffer();
            continue;
        }
        
        // Check if input too long
        if (strlen(buffer) == sizeof(buffer) - 1 && buffer[strlen(buffer) - 1] != '\n') {
            printf("Error: Input too long. Please enter a shorter number.\n");
            clearBuffer();
            continue;
        }
        
        // Change newline to null terminator
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Check for empty input
        if (strlen(buffer) == 0) {
            printf("Error: No input provided. Please enter a number.\n");
            continue;
        }
        
        // Try to convert to integer
        char *endptr;
        long result = strtol(buffer, &endptr, 10);
        
        // Check for conversion errors
        if (*endptr != '\0') {
            printf("Error: Please enter a valid whole number.\n");
            continue;
        }

        // Check for return signal
        if (result == -1) return -1;
        
        // Check range
        if (result < min || result > max) {
            printf("Error: Input must be between %d and %d.\n", min, max);
            continue;
        }
        
        input = (int)result;

        break;
    }
    
    return input;
}

double getValidDouble(const char* basePrompt, double min, double max) {
    double input;
    char buffer[100];
    char fullPrompt[150];
    
    snprintf(fullPrompt, sizeof(fullPrompt), "%s [%.2f - %.2f]: ", basePrompt, min, max); // Add the boundary to the prompt
    
    while (1) {
        printf("%s", fullPrompt);
        
        // Get input as string
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            clearBuffer();
            continue;
        }
        
        // Check if input too long
        if (strlen(buffer) == sizeof(buffer) - 1 && buffer[strlen(buffer) - 1] != '\n') {
            printf("Error: Input too long. Please enter a shorter input.\n");
            clearBuffer();
            continue;
        }
        
        // Change newline to null terminator
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Check for empty input
        if (strlen(buffer) == 0) {
            printf("Error: No input provided. Please enter a number.\n");
            continue;
        }
        
        // Try to convert to double
        char *endptr;
        double result = strtod(buffer, &endptr);
        
        // Check for conversion errors
        if (*endptr != '\0') {
            printf("Error: Please enter a valid number.\n");
            continue;
        }
        
        // Check range
        if (result < min || result > max) {
            printf("Error: Input must be between %.2f and %.2f.\n", min, max);
            continue;
        }
        
        input = result;
        break;
    }
    
    return input;
}

int getValidString(const char* prompt, char* output, int maxLength) {
    char buffer[1024];
    
    // Check for empty input
    if (output == NULL || maxLength <= 0) {
        return 0;
    }
    
    while (1) {
        printf("%s", prompt);
        
        // Get input as string
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            clearBuffer();
            continue;
        }
        
        // Check if input too long
        if (strlen(buffer) == sizeof(buffer) - 1 && buffer[strlen(buffer) - 1] != '\n') {
            printf("Error: Input too long. Maximum length is %d characters.\n", maxLength - 1);
            clearBuffer();
            continue;
        }
        
        // Change newline to null terminator
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Check if input exceed the maximum output
        if (strlen(buffer) >= maxLength) {
            printf("Error: Input too long. Maximum length is %d characters.\n", maxLength - 1);
            continue;
        }
        
        // Check if string contains only letters and spaces
        int valid = 1;
        int hasLetter = 0;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isalpha((unsigned char)buffer[i]) && buffer[i] != ' ') {
                valid = 0;
                break;
            }
            if (isalpha((unsigned char)buffer[i])) {
                hasLetter = 1;
            }
        }
        
        if (!valid) {
            printf("Error: Invalid input. Please enter only letters and spaces.\n");
            continue;
        }

        if (!hasLetter) {
            printf("Error: Invalid input. Town name must include at least one letter.\n");
            continue;
        }
        
        // Copy the valid input to output
        strncpy(output, buffer, maxLength - 1);
        output[maxLength - 1] = '\0';

        return 1;
    }
}

int getYesNoResponse(const char* prompt) {
    char input;
    char buffer[100];
    
    while (1) {
        printf("%s (y/n): ", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            clearBuffer();
            continue;
        }
        
        // Check if input too long
        if (strlen(buffer) == sizeof(buffer) - 1 && buffer[strlen(buffer) - 1] != '\n') {
            printf("Input too long. Please enter only 'y' or 'n'.\n");
            clearBuffer();
            continue;
        }
        
        // Change newline to null terminator
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Check for single character input
        if (strlen(buffer) != 1) {
            printf("Please enter a single character (y/n).\n");
            continue;
        }
        
        // Case-insensitive
        input = tolower(buffer[0]);
        if (input == 'y') {
            return 1;
        } else if (input == 'n') {
            return 0;
        } else {
            printf("Invalid input. Please enter 'y' for yes or 'n' for no.\n");
        }
    }
}

// Function to capitalize the first letter
void capitalFirstLetter(char* str) {
    if (str == NULL || str[0] == '\0') return; 

    str[0] = toupper(str[0]);
}
