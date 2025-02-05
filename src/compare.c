/*
 * =====================================================================================
 *
 *       Filename:  compare.c
 *
 *    Description: compare tool for files watched and store location 
 *
 *        Version:  1.0
 *        Created:  01/24/2025 04:55:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Brian_Tum(), 
 *   Organization:  
 *
 * =====================================================================================
*/
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sqlite3.h>
#include <string.h>

#include "source_location.h"
#include "db.h"

char *strip_path(char *path);
static char *read_backup_location();

// strip location from path i.e /media/brian or /home/brian
char *strip_path(char *path) {
    regex_t regex;
    int res;
    char *pattern = "/media/brian|/home/brian";
    res = regcomp(&regex, pattern,REG_EXTENDED);
    if (res != 0) {
    	perror("couldnt compile re");
	return NULL;
    }

    regmatch_t match;
    res = regexec(&regex, path, 1, &match, 1);
    if (res == 0) {
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
    }else if (res == REG_NOMATCH) {
    	printf("No match found\n");
	return NULL;
    } else {
    	printf("Err exec regex\n");
	return NULL;
    }
    regfree(&regex);
    return NULL;
}

// read dir from watched dir / table
//static int callback(void *NotUsed, int argc, char **argv, char **colName) {
//	DIR *dir;
//	struct dirent *entry;
//
//	for (int i=0; i< argc; i++) {
//		printf(" >- %s",strip_path(argv[i])?strip_path(argv[i]):"NULL");
//	}
//	printf("\n");
//	return 0;
//}

//void read_table() {
//	sqlite3 *conn = open_db();
//	char *sql = "SELECT path FROM compfilespaths;";
//	char *errmsg = 0;
//	int rc = 0;
//	rc = sqlite3_exec(conn,sql,callback,0,&errmsg);
//	if (rc != 0) {
//		fprintf(stderr, "read table err: %s\n", errmsg);
//		exit(2);
//	}
//	sqlite3_close(conn);
//}

// query name part 2
char **comp_files() {
	char **entries;
	int count = 0;
	int capacity = 45;
	sqlite3 *conn = open_db();
	char *sql = "SELECT path FROM compfilespaths;";
	sqlite3_stmt *stmt;
	int rc = 0;
	rc = sqlite3_prepare_v2(conn, sql, -1, &stmt,0);
	if (rc != 0){
		perror("error prep stmt");
		exit(5);
	}
	
	entries = malloc(capacity * sizeof(char*));
	if (entries == NULL) {
		perror("error entry mem alloc");
		sqlite3_finalize(stmt);
		sqlite3_close(conn);
		for(int i=0;i<count;i++) {
			free(entries[i]);
		}
		return NULL;
	}

	while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		char *names = (char*)sqlite3_column_text(stmt, 0);
		entries[count] = (char*)malloc(128 * sizeof(char)); 
		if (entries == NULL) {
			perror("error entry mem alloc");
			sqlite3_finalize(stmt);
			sqlite3_close(conn);
			for(int i=0;i<count;i++) {
				free(entries[i]);
			}
		return NULL;
		}
		strcpy(entries[count],names);
		count++;

		if (count >= capacity) {
			capacity *= 2;
			entries = realloc(entries, capacity * sizeof(char*));
			if (entries == NULL) {
				perror("error entry mem alloc");
				sqlite3_finalize(stmt);
				sqlite3_close(conn);
				for(int i=0;i<count;i++) {
					free(entries[i]);
				}
			return NULL;
			}
		}
		
	}

	if (rc != SQLITE_DONE) {
		fprintf(stderr, "read table error: %s",sqlite3_errmsg(conn));
		exit(3);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(conn);
	return entries;
}

// compare 

// copy
