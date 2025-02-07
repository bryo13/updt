/* 
 * =====================================================================================
 *
 *       Filename:  watch_locations.c
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
#include <sys/stat.h>

#include "source_location.h"
#include "db.h"
#include "watch_locations.h"

// traverse all watch locations
// gets input from returnPath()
// save in db
void traverse_all(void) {
	sqlite3 *conn = open_db();
	int len = 0;
	char **paths = returnPath();

	while(paths[len] != NULL) {
		len++;
	}

	for (int i = 0; i < len; i++) {
		traverse_incompfiles(conn, paths[i]);
	}
	printf("currently tracking: %d files\n",watched_paths(conn));
	sqlite3_close(conn);

}

// read watch file
// returns array with paths to traverse
char **returnPath(void) {
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
	free(lc);
	return paths;

}

// traverse single location from the watch
// gets a single path from traverse all
void traverse_incompfiles(sqlite3 *conn, char *path) {
	DIR *dir;
	struct dirent *entry;	
	struct stat st;

	if (!(dir = opendir(path))) {
		return;
	}
	while((entry = readdir(dir)) != NULL) {
		if(strcmp(entry->d_name,".") == 0 || strcmp(entry ->d_name, "..") == 0) {
			continue;
		}

		char pth[1024];
		snprintf(pth, sizeof(pth),"%s/%s",path,entry->d_name);
		
		if (stat(pth, &st) != 0) {
			perror("file stat error");
			continue;
		}
		// insert into table intead of printing
		if (S_ISREG(st.st_mode)) {
			//printf("%s\n",pth);
			insert_compfiles(conn, pth,&st.st_mtime, (double)st.st_size/(1024 * 1024));
		}
		if (S_ISDIR(st.st_mode)) {
			traverse_incompfiles(conn, pth);
		}
		 
	}
	closedir(dir);
}

// read path from createLocation()
char *loc(void) {
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
