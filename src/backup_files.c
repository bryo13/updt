/*
 * =====================================================================================
 *
 *       Filename:  backup_files.c
 *
 *    Description: record backed up files 
 *
 *        Version:  1.0
 *        Created:  02/03/2025 05:14:59 PM
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
#include <string.h>
#include <regex.h>
#include <sqlite3.h>
#include <dirent.h>
#include <sys/stat.h>

#include "source_location.h"
#include "backup_files.h"
#include "db.h"

// remove prefex of watched location
// 	to compare if remaining path is present or needs inserting
char *remove_prefix(char *path) {
	regex_t regex;
	int rc;
	char *pattern = "/home/brian/";

	rc = regcomp(&regex, pattern, REG_EXTENDED);
	if (rc != 0) {
		perror("error compiling regex for backup files");
		return NULL;
	}
	regmatch_t match;
	rc = regexec(&regex, path, 1, &match, 1);
	if (rc == 0) {
		int start = match.rm_so;
		int end = match.rm_eo;
		int len = end - start;

		char *unmatched = (char*)malloc(len + 1); 
		if (unmatched == NULL) {
			perror("error matched mem alloc");
			return NULL;
		}
		int char_to_cpy = strlen(path) - len;
		strncpy(unmatched, path + len, char_to_cpy);
		unmatched[char_to_cpy] = '\0';

		return unmatched;
	}else if (rc == REG_NOMATCH) {
		printf("No match found\n");
		regfree(&regex);
		return NULL;
	} else {
		printf("Err exec regex\n");
		regfree(&regex);
		return NULL;
	}
	regfree(&regex);
	return NULL;

}

// returns backup media path
char *read_backup_location() {
	FILE *file;
	const char *loc = pref_loc();
	char *bl = (char*)malloc(128 * sizeof(char));
	if (bl == NULL) {
		perror("error backup loc mem alloc");
		exit(2);
	}
	char read[122];
	file = fopen(loc, "r");
	if (file == NULL) {
		perror("prefered location read err");
		exit(3);
	}

	while(fgets(read, sizeof(read), file)) {
		strcpy(bl, read);
		break;
	}
	int len = strlen(bl);
	bl[len] = '\0';
	bl[strcspn(bl, "\n")] = 0;
	return bl;
}

// read watch file
char **watched() {
	char *watched = "/home/brian/.updt/watch";
	char **to_be_watched;
	int count = 0;
	int capacity = 45;
	FILE *file;
	char buffer[128];

	to_be_watched = malloc(capacity * sizeof(char*));
	if (to_be_watched == NULL) {
		perror("cant alloc mem for watch location");
		exit(1);
	}

	if ((file = fopen(watched, "r")) == NULL ) {
		perror("Cant read watch file");
		exit(2);
	}

	while(fgets(buffer, sizeof(buffer), file) != NULL) {
		to_be_watched[count] = (char*)malloc(sizeof(buffer) + 1);	
		if (to_be_watched[count] == NULL) {
			perror("err mem alloc");
			exit(2);
		}
		buffer[strcspn(buffer,"\n")] = '\0';
		strcpy(to_be_watched[count], buffer);
		count++;

		if (count >= capacity) {
			capacity *= capacity;
			to_be_watched = realloc(to_be_watched, capacity * sizeof(char*));
			if (to_be_watched == NULL) {
				perror("failed to realloc to be read mem");
				exit(2);
			}
		}
	}
	to_be_watched[count] = NULL;
	fclose(file);
	return to_be_watched;
}

// traverse backup location
void traverse_backup(sqlite3 *conn, char *path, char *compare) {
	struct dirent *entry;
	struct stat st;
	DIR *dir;

	if (!(dir = opendir(path))) {
		perror("Can open dir path");
		exit(2);
	}

	while ((entry = readdir(dir)) != NULL) {
		if(strcmp(entry->d_name,".") == 0 || strcmp(entry ->d_name, "..") == 0) {
			continue;
		}

		char pth[1024];
		snprintf(pth, sizeof(pth),"%s/%s",path,entry->d_name);

		if ((stat(pth, &st) == 0) && (S_ISREG(st.st_mode))) {
			// only files similar in path names 
			if (strstr(pth, compare) != NULL){
				// insert
				printf("Doesnt need to be tracked: %s\n",pth);
			}
			
		}
		if (S_ISDIR(st.st_mode)) {
			traverse_backup(conn, pth, compare);
		}
	}
}

void check_all(void) {
	char *path = read_backup_location();
	sqlite3 *conn = open_db();
	int count = 0;
	char **wtchd = watched();

	while(wtchd[count] != NULL) {
		count++;
	}
	for (int i=0;i<count;i++) {
		char *compare = remove_prefix(wtchd[i]);
		traverse_backup(conn, path, compare);
	}
	sqlite3_close(conn);
	free(path);
	for (int i=0;i<count;i++) {
		free(wtchd[i]);
	}
	free(wtchd);
}