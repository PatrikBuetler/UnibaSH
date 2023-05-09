#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "matchUserInput.h"

// To compile use: make
// To run use: ./main

void clear();
void splitInput(char input[]);

int main() {
    // First time setup
    
    char pathname, input[101];
    clear();
    
    // Main while loop
    
    // Scan for user input and execute it
    while(1) {
        scanf("%[^\n]%*c", input); 
        // scanset [^\n] says, read everything until newline. so this reads more than just 1 word
        int result = matchUserInput(input);
        printf("Successfully parsed %s, return to main with exit code %d\nUnibaSH$ ", input, result);
    }
    return 0;

}
