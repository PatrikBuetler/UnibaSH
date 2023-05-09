#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>	

void clear();
static const char* CLEAR_SCREEN = "\e[H\e[2J\e[3J"; // alternative "\e[1;1H\e[2J" see asci escape codes

int matchUserInput(char *input) {
// returns 1 if cmd is valid and implemented or -1 (or undefined) if not found

    // strcmp returns 0 when the string is the same, so we need to invert it
    if(!strcmp(input, "clear") || !strcmp(input, "clear()")) {
        clear();
        return 1;
    }
    
    if(!strcmp(input, "help") || !strcmp(input, "help()")) {
        // TODO
    }
    
    if(!strcmp(input, "login") || !strcmp(input, "login()")) {
        // TODO
    }
    
    if(!strcmp(input, "ls")) {
        // from the man page of scandir
        struct dirent **list;
        int i = scandir(".", &list, NULL, alphasort);
        while(i--) {
            printf("%s\n", list[i]->d_name);
            free(list[i]);
        }
        free(list);
        return 1;
    }
    
    if(!strncmp(input, "./", strlen("./"))) { // Check if command starts with ./ to run something
        char *progName = input+2;
        printf("Executing %s\n", progName);
        
        int status = system(input);
        
        printf("UnibaSH$ ");
        return 1;
    }
    else {
        printf("UnibaSH$ ");
        return -1;
    }

}

void clear() {
    // Clears the shell to the default state
    // Maybe make a windowControl.h or similar
    
    printf("%s", CLEAR_SCREEN);
    printf("Welcome to UnibaSH! Use clear, help, quit, login or anything else\n");
    printf("UnibaSH$ ");
}
void splitInput(char *input) {
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
    //int result = matchUserInput(cmd, args);
    //printf("Successfully parsed %s, return to main with exit code %d\nUnibaSH$ ", cmd, result);
}
