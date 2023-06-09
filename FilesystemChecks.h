int checkIfFolderExists(char* value); //search for the keywords ending with -h, return 1 if folder exists
void checkForUnregisteredChanges(); // Check if textFile was changed inbetween sessions and ask User if he wants to create it now
char* getDictionaryOfFoldersAndFiles(); // Read textFile.txt and create a struct
void copyPdfToFolder(char* pdfName, char* folderName);
int checkFileAge(char* fileName);
void archiveOldFiles();
void checkIfArchiveExists();
void checkIfSubfolderExists(char where, char target);
int getCurrentYear();
char* extractFilenameFromAlias(char course[], char lorh[], char number[], char year[]); // parameters taken from getAlias of c.c
void checkAndCreateSecondLayerFolder(char *year);
void checkAndCreateThirdLayerFolder(char *lecture, char *year);
void checkAndCreateFourthLayerFolder(char *lorh, char *lecture, char *year);
void moveFileToLayerFolder(char folder, char name);
void checkAndCreatePath(char *path);
char* constructFilepath(char *lecture, char *year, char *lorh, char);
