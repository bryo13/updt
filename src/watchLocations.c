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

// read watch file
// returns array with paths to traverse
char **returnPath()
{
	char **path = (char *)malloc(16384 * sizeof(char));
	return path;
}

// traverse all watch locations
// gets input from returnPath()
// save in db
void traverseAll(char **paths)
{
	int len = sizeof(paths) / sizeof(paths[0]);
	for (int i = 0; i < len; i++)
	{
		traverseSingle(paths[i]);
	}
}

// traverse single location from the watch
// gets a single path from traverse all
void traverseSingle(char *path) {
	DIR *dir;
	struct dirent entry;	

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


