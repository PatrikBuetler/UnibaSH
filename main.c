#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "matchUserInput.h"

// To compile use: make
// To run use: ./main

void clear();

void parseInput(char input[]) {
    // This clear command can go into the other class. This was done for testing purposes.
    // Make this method splice the input better in case input is command + attributes behind it
    // Then send the command to the other class
    // split the input through white spaces to separate the command and the attributes coming with it
    
    char delimiter[] = " "; // split the input string at those characters, example ",;._"
    char *cmd; 
    char *next; // pointer to the next split word in the string
    char *args[100];
    int i=0;
    
    // Take first word (until whitespace is detected) and save if as cmd
    next = strtok(input, delimiter);
    //printf("command found %s\n", next);
    cmd = next;
    do {
        // Jump to next word starting at the next whitespace, first argument is NULL because
        // only in the first method call you need to specify the starting point
        next = strtok(NULL, delimiter);
        // if we have another input it is a argument, save it to the args array
        if (next != NULL) {
            args[i] = next;
            //printf("args found %s\n", args[i]);
            i++;
        }    
    } while(next != NULL);
    
    // result returns 1 if cmd is valid and implemented or -1 (or undefined) if not found
    int result = matchUserInput(cmd, args);
}

int main() {
    // First time setup
    
    // argv will be used in execve to execute programs
    // pathname might be needed there as well. 
    char pathname, input[101], argv[100];
    clear();
    
    // Main while loop
    
    // Scan for user input and execute it
    while(1) {
        scanf("%[^\n]%*c", input); 
        // scanset [^\n] says, read everything until newline. so this reads more than just 1 word
        parseInput(input);
    }
    return 0;

}
