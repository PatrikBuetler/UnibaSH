#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void clear();
static const char* CLEAR_SCREEN = "\e[H\e[2J\e[3J"; // alternative "\e[1;1H\e[2J" see asci escape codes

int matchUserInput(char *input, char *args[]) {
    // strcmp returns 0 when the string is the same, so we need a ! here
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
        // TODO
    }
    if(!strcmp(input, "./*") || !strcmp(input, "./*")) { // Check if command starts with ./ to run something
        // TODO
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
