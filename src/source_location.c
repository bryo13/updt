/*
 * =====================================================================================
 *
 *       Filename:  store_location.c
 *
 *    Description: create a dir in the home dir that
 *                 will be used to house source config
 *
 *        Version:  1.0
 *        Created:  01/19/2025 10:08:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Brian_Tum(),
 *   Organization:
 *
 * =====================================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

#include "source_location.h"

// returns home dir
const char *homepath(void) {
	char *homedir = (char*)malloc(30 * sizeof(char));
	if (homedir == NULL) {
		perror("err mem allc for homedir path");
		return NULL;
	}
#ifdef __linux__
	homedir = getenv("HOME");
#else
	printf("Not linux system\n");
#endif

	if (homedir)
	{
		return homedir;
	}
	else
	{
		perror("Couldnt find getenv HOME\n");
	}
	return NULL;
}

// will host data file in home dir
const char *create_location(void) {
	const char *home = homepath();
	if (home == NULL) {
		perror("err getting home path");
		exit(2);
	}

	char *store = (char *)malloc(30 * strlen(home));
	if (store == NULL){
		perror("Error mem allocation");
		exit(2);
	}

	strcpy(store, home);
	strcat(store, "/.updt");

	struct stat sbuf;
	if (stat(store, &sbuf) == 0){
		return store;
	}

	if (mkdir(store, 0755) == 0){
		return store;
	}

	return NULL;
}

// where to write pref location
const char *pref_loc(){
	const char *hm = homepath();
	char *pb = (char*)malloc(128 * sizeof(char));
	if (pb == NULL) {
		perror("prefered backup mem aloc err");
		return NULL;
	}
	strcpy(pb,hm);
	strcat(pb, "/.updt/pref");
	return pb;
} 
