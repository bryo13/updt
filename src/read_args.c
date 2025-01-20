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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./includes/store_location.h"

// writes location/s to watch
void writeArgs(int argCount, char *argVect[]) {
    char* path = create_location();
    FILE *file;

    strcat(path, "/watch");
    if ((file = fopen(path, "a")) == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i=0; i<argCount; i++) {
        fprintf(file,"%s\n", argVect[i]);
    }
    fclose(file);
}