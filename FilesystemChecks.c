#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include "matchUserInput.h"
#include <pwd.h>

void moveFileToLayerFolder(char folder, char name);
int checkIfFolderExists(char* value) {
    DIR* dir = opendir(value);
    if(dir) {
    	// exists
    	return 1;
    }
    else {
        // doesn't exist yet
        return -1;
    }
}

void checkForUnregisteredChanges() {
    // TODO go through textFile.txt and check if all those folders exist, maybe check if all .pdf's are also present? idk
}

char* getFoldersAndFiles() {
    
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char *file = "textFile.txt";
    FILE *fp = fopen(file,"r");

    if(fp == NULL) {
        printf("Error opening file");
    }

    while((read = getline(&line, &len, fp)) != -1) {
        //printf("line:");
        //printf(line);
        if (strstr(line, "-h {") != NULL) {
            // TODO Entry in textFile.txt found, now what?
        }
    }
    free(line);
    fclose(fp);

}

void copyPdfToFolder(char* pdfName, char* folderName) {
    // TODO pdf might be in another folder. potentionally need full path to file
    if(checkIfFolderExists(folderName)) {
        int status = system("cp pdfName folderName");
        if(status == -1) {
            printf("Error in system(cp pdfName folderName)");
        }
    }  
    else {
        printf("Error with %s", folderName);
    }
}
int checkFileAge(char* fileName) {
    //printf("Checking %s's age..\n", fileName);
    struct stat file_stats;
    // this statement seems strange
    //if(stat(fileName, &file_stats) != 0) {
    //    printf("Error in stat\n");
    //	return -1;
    //}
    if(strcmp(fileName, "..") == 0 || strcmp(fileName, ".") == 0) {
    	return -1;
    }
    else {
        time_t current_time = time(NULL);
        time_t age_in_seconds = difftime(current_time, file_stats.st_mtime);
        int age_in_days = age_in_seconds / (60*60*24);
        printf("A file named %s with age %d found\n", fileName, age_in_days);       
        return age_in_days;       
    }
    return -1;
}
void checkIfArchiveExists() {
    struct stat entry;
    if(stat("Archive", &entry) == -1) {
        mkdir("Archive", 0777);
    }
}

void checkIfSubfolderExists(char* target) {
    struct stat entry;
    char path[50] = "./Archive/";
    strcat(path, target);
    if(stat(path, &entry) == -1) {
        mkdir(path, 0777);
    }
}

void archiveOldFiles() {

    int AGETOARCHIVEINDAYS = 30;
    DIR* dir;
    struct dirent *entry;
    struct stat entry_stat;
    char currentDir[150] = ".";
    dir = opendir(currentDir); // open current directory aka. UnibaSH Folder
    
    // Loop over all files in UnibaSH Folder
    while ((entry = readdir(dir)) != NULL) {
        //printf("Found %s\n", entry->d_name);
        
        // get the Stats of the found file
        stat(entry->d_name, &entry_stat);
        // If found file is a folder and not one of the standard folders such as . or .. or .gitignore
        if (S_ISDIR(entry_stat.st_mode) && strcmp(entry->d_name, "..")!= 0 && strcmp(entry->d_name, ".")!= 0 && strcmp(entry->d_name, ".git")!= 0 && strcmp(entry->d_name, "Archive")!= 0) {
            // Folder found, check the files inside using checkFileAge
            printf("Checking the folder %s for files to archive...\n", entry->d_name);
            char* currentDir2 = entry->d_name;
            //strcat(currentDir2, entry->d_name); //build the relative file path
            //printf("New folder Target: %s\n", currentDir);
            
            // Found a folder, prepare to loop over all its content
            DIR* dir2 = opendir(currentDir2);
            struct dirent *entry2;
            struct stat entry_stat2;
            while ((entry2 = readdir(dir2))!= NULL) {
                char relativePathToFile[50] = "";
                strcat(relativePathToFile, entry->d_name);
                strcat(relativePathToFile, "/");
                strcat(relativePathToFile, entry2->d_name);
                stat(relativePathToFile, &entry_stat2);
            	if(checkFileAge(entry2->d_name) >= AGETOARCHIVEINDAYS) {
            	    // TODO partially TESTED! copys the file to archive but do
            	    printf("Attempting to archive %s\n", entry2->d_name);
            	    checkIfArchiveExists();
            	    checkIfSubfolderExists(entry->d_name);
            	    char* fileName2 = relativePathToFile;
            	    char target2[50] = "./Archive/"; // Build the target structure for archive
            	    strcat(target2, entry->d_name);
            	    char command[100];
            	    snprintf(command, sizeof(command), "cp %s %s", fileName2, target2);
            	    printf("%s\n", command);
            	    int status = system(command);
        	    if(status == -1) {
                        printf("Error in system(cp pdfName folderName)");
                        // return here because the next step is to delete the original
                        break;
                    }
                    // Remove original file
                    if (remove(fileName2) != 0) {
                    	perror("Error deleting\n");
                    }
                    
            	}
            }
            closedir(dir2);           
        }
    }  
    closedir(dir);
}
//Get the current year
int getCurrentYear() {
    int current_year;
    int current_month;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    current_year = tm->tm_year + 1900;
    current_month = tm->tm_mon + 1;

    if (current_month == 1) {
        return current_year - 1;
    }
    //printf("%d", current_year);
    return current_year;
}
char* extractFilenameFromAlias(char* arg1, char* arg2, char* arg3, char* arg4) {

    char *file = "textFile.txt";
    FILE *fp = fopen(file,"r");
    char chosen_year[2];
    size_t len = 150;
    char *line = NULL;
    ssize_t read;
    int x=0;
    char name[30];
    char *filename;
    //if (!year) {
    //    int current_year = getCurrentYear();
    //    snprintf(chosen_year, sizeof(chosen_year), "%d", current_year);
    //} else {
    //    strcpy(chosen_year, year);
    //}
    if(fp == NULL) {
        printf("Error opening file");
    }
    while((read = getline(&line, &len, fp)) != -1) {
        //printf("line:");
        //printf("%s", line);
        if (strstr(line, arg1) != NULL && strstr(line, arg2) != NULL) {// YEAR NOCH EGAL && strstr(line, &year) != NULL) {
            x = 1;
        }
        //if (!strcmp(line, "}")) {
            //printf("exit:");
            //printf(line);
        //    printf("The sheet or slide does not exist\n");
        //    break;
        //}
        if (strstr(line, arg3) && x == 1) {
        // arr is the line from alias where its sheetname|linktosheet and we then get the link in link. then search link for strstr="file=" and strtok(NULL, "&") to receive file name
            filename = strtok(line, "|");
            //filename = strtok(NULL, "|");
            filename = strtok(NULL, "=");
            filename = strtok(NULL, "=");
            filename = strtok(NULL, "&");
            //printf("Filename: %s\n", filename);
            strcpy(name, filename);
            //printf("name: %s\n", name);
            break;
        }
    }
    fclose(fp);
    free(line);
    if(x==0) {
        printf("Exercise not found");
    }
    return filename; 
}
void checkAndCreatePath(char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
    }
    else if (ENOENT == errno) {
        if (mkdir(path, 0777) == 0) {
            // created successfully
        }
        else {
            // creation failed
        }
    }
}
void checkAndCreateSecondLayerFolder(char *year){
    char path[50] = "UnibaSH/";
    strcat(path, year);
    checkAndCreatePath(path);
}
void checkAndCreateThirdLayerFolder(char *lecture, char *year){
    char path[50] = "UnibaSH/";
    strcat(path, year);
    strcat(path,"/");
    strcat(path, lecture);
    //printf("%s\n", path);
    checkAndCreatePath(path);
}

char* checkAndCreateFourthLayerFolder(char *lorh, char *lecture, char *year) {
    char path[50] = "UnibaSH/";
    strcat(path, year);
    strcat(path,"/");
    strcat(path, lecture);
    strcat(path, "/");
    if (!strcmp(lorh, "h")) {
        strcat(path, "Homework");
    }
    else {
        strcat(path, "Lecture");
    }
    //printf("%s\n", path);
    checkAndCreatePath(path);
    char *ret = malloc(50*sizeof(char));
    strcpy(ret, path);
    return ret;
}
void moveFileToLayerFolder(char folder, char name){

}
char* constructFilepath(char *lecture, char *year, char *lorh) {
    char path[50] = "UnibaSH/";
    strcat(path, year);
    strcat(path,"/");
    strcat(path, lecture);
    strcat(path, "/");
    if (!strcmp(lorh, "h")) {
        strcat(path, "Homework");
    }
    else {
        strcat(path, "Lecture");
    }
    //printf("%s\n", path);
    //checkAndCreatePath(path);
    char *ret = malloc(50* sizeof(char)); 
    strcpy(ret, path);
    return ret;
}
char* getDownloadPath() {
    const char *home;
     if((home = getenv("HOME")) == NULL) {
         //home = getpwuid(getuid())->pw_dir;
     }
     
    char *homepath = malloc(30*sizeof(char));
    strcat(homepath, home);
    strcat(homepath, "/Downloads");

    //printf("%s\n", homepath);
    return homepath;
}



