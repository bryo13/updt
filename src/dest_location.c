/*
 * =====================================================================================
 *
 *       Filename:  dest_location.c
 *
 *    Description: returns chosen location from a potential list 
 *			reads from /media/brian in my sys
 *        Version:  1.0
 *        Created:  01/27/2025 06:24:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BrianTum(), 
 *   Organization:  
 *
 * =====================================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/statvfs.h>

#include "dest_location.h"
#include "source_location.h"

// returns backup locations
char **backup_locations(void) {
    char **path = NULL;
    int count = 0;
    char *backup_location = "/media/brian";
    struct dirent *entry;
    DIR *dir;
    path = malloc(256 * sizeof(char*));
    if (path == NULL) {
        perror("cant alloc mem for paths array");
        return NULL;
    }

    dir = opendir(backup_location);
    if (dir == NULL) {
        perror("error opening backup location");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)) {
			continue;		
		}
        path[count] = (char*)malloc(128 * sizeof(char));
        if (path[count] == NULL) {
            perror("err allc ary");
			for (int i=0;i<count;i++) {
				free(path[i]);
			}
			free(path);
			closedir(dir);
			return NULL;
        }
        path[count] = strdup(entry->d_name);
        count++;
    }
    path[count] = NULL;
    closedir(dir);
    return path;
}

// select prefered
char *prefered(void) {
    char **paths = backup_locations();
    int len = 0;
    int i = 0;
    char *path_start = "/media/brian/";
    char *pref = (char*)malloc(128 * sizeof(char));
    if (pref == NULL) {
        perror("failed to alloc prefered mem");
        return NULL;
    }
    strcpy(pref, path_start);
    while(paths[len] != NULL) {
        len++;
    }

    if (len < 1) {
        printf("Couldnt find  backup locations\n");
        return NULL;
    } else if (len == 1) {
        strcat(pref, paths[0]);
        printf("only found \033[1m%s\033[0m, will be used by default\n", pref);
        remaining(pref);
        return pref;
    } else {
        printf("Choose your prefered location by picking the no accociated\n");
    }

    for (i = 0; i< len; i++ ){
        printf("%d for %s\n",i+1,paths[i]);
    }
    free(paths);
    return NULL;
}

// write prefered
void write_prefered(void) {
    char *pref = prefered();
    if (pref == NULL) {
        perror("Cant read backup location");
        return;
    }
    FILE *file;
    const char *write_loc = create_location();
    char *pref_file = (char*)malloc(128 * sizeof(char));
    if (pref_file == NULL) {
        perror("err alloc pref file path");
        return;
    }
    strcpy(pref_file, write_loc);
    strcat(pref_file, "/pref");

    if ((file = fopen(pref_file, "w")) == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }

    fprintf(file, "%s\n", pref);
    free(pref_file);
    fclose(file);
}

// check backup space available
void remaining(char *path) {

    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        perror("statvfs err");
        return;
    }

    unsigned long long free_space = stat.f_bavail * stat.f_bsize;
    printf("\t and has \033[1m%lld GB\033[0m free\n", free_space / (1024*1024*1024));
}
