/*
 * =====================================================================================
 *
 *       Filename:  watchLocations.c
 *
 *    Description: The dir one wants to watch, the files and sub dir are stored in sqlite
 *    		        table as paths
 *        Version:  1.0
 *        Created:  01/22/2025 10:17:24 AM
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
#include <dirent.h>
#include "./includes/store_location.h"

char **returnPath();
void traverseAll();
void traverseSingle();
char *loc();

// read watch file
// returns array with paths to traverse
char **returnPath() {
	FILE *file;
	char *lc = loc();
	int count = 0;
	int capacity = 13;
	char buffer[124]; // hold a single line
	char **paths = NULL;

	file = fopen(lc, "r");
	if (file == NULL) {
		perror("error opening watch file");
		return NULL;
	}
	paths = malloc(capacity * sizeof(char*));
	if (paths == NULL) {
		perror("err allc ary");
		fclose(file);
		return NULL;
	}

	while(fgets(buffer, sizeof(buffer), file)) {
		size_t len = strlen(buffer);
		if (((int)len >= 0) && (buffer[(int)len - 1] == '\n')) {
			buffer[len - 1] = '\0';		
		}

		paths[count] = (char*)malloc((len + 1) * sizeof(char));
		if (paths[count] == NULL) {
			perror("err allc ary");
			for (int i=0;i<count;i++) {
				free(paths[i]);
			}
			free(paths);
			fclose(file);
			return NULL;
		}
		strcpy(paths[count], buffer);
		count++;

		if (count >= capacity) {
			capacity *= 2;
			paths = realloc(paths, capacity * sizeof(char*));
			if (paths == NULL) {		
				perror("error allc mem");
				for(int i = 0; i< count; i++) {
					free(paths[i]);
				}
				free(paths);
				fclose(file);
				return NULL;
			}
		}
	}
	fclose(file);
	return paths;
}

// traverse all watch locations
// gets input from returnPath()
// save in db
void traverseAll()
{
	char **paths = returnPath();
	size_t len = sizeof(paths) / sizeof(paths[0]);
	for (int i = 0; i < len; i++)
	{
		traverseSingle(paths[i]);
	}
}

// traverse single location from the watch
// gets a single path from traverse all
void traverseSingle(char *path) {
	DIR *dir;
	struct dirent *entry;	

	if (!(dir = opendir(path)))
	{
		return;
	}
	while((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			char pth[5860];
			if(strcmp(entry->d_name,".") == 0 || strcmp(entry ->d_name, "..") == 0) {
				continue;
			}

			snprintf(pth, sizeof(pth),"%s/%s",path,entry->d_name);
			// insert into table intead of printing
			printf("%s\n",pth);
			traverseSingle(pth);
		} else {
			// insert into table intead of printing
			printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
}

// read path from createLocation()
char *loc() {
	const char *location = create_location();
	char *lc = (char*)malloc(13 * sizeof(char));
	if (lc == NULL) {
		perror("err mem alloc");
		return NULL;
	}

	strcpy(lc, location);
	strcat(lc, "/watch");
	return lc;
}
