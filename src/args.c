/*
 * =====================================================================================
 *
 *       Filename:  read_args.c
 *
 *    Description: reads and write args from stdin
 *                   
 *
 *        Version:  1.0
 *        Created:  01/20/2025 05:33:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./includes/store_location.h"

int isPathValid(char *path);
int isPathAlreadyWatched(char *path, char *fileLocation);

// writes location/s to watch
void writeArgs(int argCount, char *argVect[]) {
    const char *path = create_location();
    const char *home = homepath();
    FILE *file;

    /// location to store records to be watched
    char *argsStorePath = (char *)malloc(strlen(path) * 10);
    if (argsStorePath == NULL) {
        perror("Error allocating args store path str");
        exit(2);
    }
    strcpy(argsStorePath, path);
    strcat(argsStorePath, "/watch");
    if ((file = fopen(argsStorePath, "a")) == NULL) {
        perror("Error opening file");
        return;
    }

    // location user wants to watch
    char *argsLocation = (char *)malloc(strlen(home) * 10);
    if (argsLocation == NULL) {
        perror("Error allocating args store path str");
        exit(2);
    }

    // original state of the string to avoid appending in every iter 
    char *OriginalState = (char *)malloc(strlen(argsLocation) * 10);
    if (argsLocation == NULL) {
        perror("Error allocating args store path str");
        exit(2);
    }

    strcpy(argsLocation, home);
    strcat(argsLocation, "/");
    strcpy(OriginalState, argsLocation);
    for (int i=1; i<argCount; i++) {
        strcat(argsLocation, argVect[i]);
        int valid = isPathValid(argsLocation);
        if (valid != 0)  {
            printf("- \033[31m%s does not exist\033[0m\n", argsLocation);
            strcpy(argsLocation, OriginalState);
            continue;
        }

        if (isPathAlreadyWatched(argsLocation, argsStorePath) != 0) {
            printf("- \033[31m%s already watched\033[0m\n", argsLocation);
            strcpy(argsLocation, OriginalState);
            continue;
        }
        printf("- %s set to be watched\n", argsLocation);
        fprintf(file,"%s\n", argsLocation);
        strcpy(argsLocation, OriginalState);
    }
    fclose(file);
}

// check if path is valid
int isPathValid(char *path) {
    struct stat sbuf;
    if (stat(path, &sbuf) == 0) {
        return 0;
    }
    return 1;
}

// check if file is already checked
int isPathAlreadyWatched(char *path, char *fileLocation) {
    FILE *file;
    char *read = (char*)malloc(8 * sizeof(char));
    if (read == NULL) {
        perror("error mem alloc for read watch file");
        return 1;
    }
    if ((file = fopen(fileLocation, "r")) == NULL) {
        perror("error getting watch file");
        return 1;
    }

    while(fgets(read, sizeof(read),file) != NULL) {
        if(strcmp(read, path) != 0) {
		printf("%s is already watched\n",path);
		return 1;
	}
    }
    	if (fclose(file) != 0) {
		perror("Error closing file");
		return EXIT_FAILURE;
	}

	return 0;

}
