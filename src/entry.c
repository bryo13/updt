/*
 * =====================================================================================
 *
 *       Filename:  start.c
 *
 *    Description: program's entry point 
 *
 *        Version:  1.0
 *        Created:  01/27/2025 10:11:54 AM
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
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "./includes/db.h"
#include "watch_args.c"
#include "watch_locations.c"

static void explainer(void);
static void checkdb_exists(void);
static void watch_init(int length, char *vec[]);

void entrypoint(int argc, char *argv[]) {
	checkdb_exists();
	if (argc < 2) {
		explainer();
	} else if ((argc > 2) && (strcmp(argv[1],"--watch") == 0)) {
		watch_init(argc, argv);
	} else {
		printf("- couldnt find %s command\n",argv[2]);
		explainer();
	}
}

static void explainer(void) {
	printf("\033[34m No args were noted, available options include:\033[0m\n");
	printf("\033[34m    --watch location sets the location to be watched \n \ti.e ./updt --watch Documents\033[0m\n");
	printf("\033[34m    --unwatch location removes watched location \n \t i.e ./updt --unwatch Documents\033[0m\n \t\033[31m cant be reversed and all config will be start from scratch\033[0m\n");
}

static void checkdb_exists(void) {
	struct stat pth, dpth;
	char path[] = "/home/brian/.updt";
	char db_path[] = "/home/brian/.updt/updt.db";

	if ((stat(path,&pth), 0) || (stat(db_path, &dpth),0)) {
		printf("Set up already");
	} else {
		db_init();
	}
}

static void watch_init(int length, char *vec[]) {
	writeArgs(length, vec);	
	traverseAll();
}