#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <dirent.h>	
#include "FilesystemChecks.h"

void splitInput(char *input);
void clear();
static const char* CLEAR_SCREEN = "\e[H\e[2J\e[3J"; // alternative "\e[1;1H\e[2J" see asci escape codes
char *lecture, *lorh, *number;
char *year = "23";
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
    if(!strcmp(input, "Adam") || !strcmp(input, "login()")) {
        // TODO
    }
    if(!strcmp(input, "test") || !strcmp(input, "login()")) {
        checkAndCreateSecondLayerFolder(year);
        return 1;
    }
    if(!strcmp(input, "quit") || !strcmp(input, "quit()") || !strcmp(input, "exit") || !strcmp(input, "exit()")) {
        exit(0);
        return 1;
    }
    if(!strncmp(input, "dl", strlen("dl"))) {
        // This is a test, we assume that a file is located in downloads folder
        char *temp = input;
        splitInput(temp);
        //printf("%s %s %s %s\n", arg1, arg2, arg3, arg4);
        // Get the name of the newly downloaded file
        char* name = extractFilenameFromAlias(lecture, lorh, number, year);
        printf("A document has been located, moving it to the corresponding folder..\n");
        checkAndCreateSecondLayerFolder(year);
        checkAndCreateThirdLayerFolder(lecture, year);
        char[] path = checkAndCreateFourthLayerFolder(lorh, lecture, year);
        // Check if we have this file already in our structure, copy it over if not
        
        //THIS IS NEW NOT IMPLEMENTED OR TESTED
        moveFileToLayerFolder(char path, char name);
        return 1;
    }

    if(!strcmp(input, "archive") || !strcmp(input, "archive()")) {
        archiveOldFiles();
        return 1;
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
void splitInput(char *temp) {
    // This method splices the input of 4 words command + 3 attributes behind it
    // split the input through white spaces to separate the command and the attributes coming with it
    // example input dl tocs h 02
    char delimiter[] = " "; // split the input string at those characters, example ",;._"
    char *next; // pointer to the next split word in the string, we dont loop over next here to simplicity
    next = strtok(temp, delimiter);
    lecture = strtok(NULL, delimiter);
    lorh = strtok(NULL, delimiter);
    // ATTENTION, third argument can be a exercise number (int, not string), without #include <stddef.h> this wont work
    number = strtok(NULL, delimiter);
    year = strtok(NULL, delimiter);
}
