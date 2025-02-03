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

char *remove_prefix(char *path);
char *read_backup_location();
char *watched_files(sqlite3 *conn, char *path);
void watch_all();

// remove prefix /home/brian
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

// know which files to watch
char *watched_files(sqlite3 *conn, char *path) {
	
}

void watch_all() {}
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

// only watch 
// insert backup
