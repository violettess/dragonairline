#ifndef UTILITY_H
#define UTILITY_H

#include <ctype.h>
#include "structs.h"

// Splash screen and main menu
void splashScreen();
int mainMenu();
void exitProgram(Graph *graph);

// Utility functions
void clearBuffer();
void capitalFirstLetter(char* str);

// Input validation
int getValidInt(const char* basePrompt, int min, int max);
double getValidDouble(const char* basePrompt, double min, double max);
int getValidString(const char* prompt, char* output, int maxLength);
int getYesNoResponse(const char* prompt);

#endif 
