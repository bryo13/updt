/*
 * =====================================================================================
 *
 *       Filename:  read_args.c
 *
 *    Description: reads and write args from stdin
 *                  to file
 *
 *
 *        Version:  1.0
 *        Created:  01/20/2025 05:33:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Brian_Tum(),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "source_location.h"
#include "watch_args.h"

// writes location/s to watch
void writeArgs(int argCount, char *argVect[]) {
    const char *path = create_location();
    const char *home = homepath();

    if ((path == NULL) || (home == NULL)) {
        perror("error getting home path");
        exit(2);
    }
    FILE *file;

    /// location to store records to be watched
    char *argsStorePath = (char *)malloc(strlen(path) * 128);
    if (argsStorePath == NULL) {
        perror("Error allocating args store path str");
        exit(2);
    }
    strcpy(argsStorePath, path);
    strcat(argsStorePath, "/watch");
    if ((file = fopen(argsStorePath, "a")) == NULL){
        perror("Error opening file");
        return;
    }

    // location user wants to watch
    char *argsLocation = (char *)malloc(strlen(home) * 120);
    if (argsLocation == NULL)
    {
        perror("Error allocating args store path str");
        exit(2);
    }

    // original state of the string to avoid appending in every iter
    char *OriginalState = (char *)malloc(strlen(argsLocation) * 128);
    if (argsLocation == NULL)
    {
        perror("Error allocating args store path str");
        exit(2);
    }

    strcpy(argsLocation, home);
    strcat(argsLocation, "/");
    strcpy(OriginalState, argsLocation);
    for (int i = 2; i < argCount; i++)
    {
        strcat(argsLocation, argVect[i]);
        int path_valid = isPathValid(argsLocation);
        int is_path_watched = isPathAlreadyWatched(argsLocation, argsStorePath);
        if ((path_valid != 0) || (is_path_watched != 0))
        {
            strcpy(argsLocation, OriginalState);
            continue;
        }

        printf("- %s set to be watched\n", argsLocation);
        fprintf(file, "%s\n", argsLocation);
        strcpy(argsLocation, OriginalState);
    }
    fclose(file);
    free(argsStorePath);
    free(argsLocation);
    free(OriginalState);
}

// check if path is valid
int isPathValid(char *path) {
    struct stat sbuf;
    if (stat(path, &sbuf) == 0) {
        return 0;
    }
    printf("- \033[31m%s does not exist\033[0m\n", path);
    return 1;
}

// check if file is already checked
int isPathAlreadyWatched(char *path, char *fileLocation) {
    FILE *file;
    char read[256]; 
    if ((file = fopen(fileLocation, "r")) == NULL) {
        perror("error getting watch file");
        return 1;
    }

    while (fgets(read, sizeof(read), file) != NULL){
        read[strcspn(read,"\n")] = '\0';

        int cmp = strcmp(read, path);
        if (cmp == 0){
            printf("- \033[31m%s already watched\033[0m\n", path);
            return 1;
        }
    }
    if (fclose(file) != 0){
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
