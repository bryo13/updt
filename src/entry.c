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

#include "watch_args.h"
#include "watch_locations.h"
#include "db.h"
#include "dest_location.h"
#include "entry.h"

void entrypoint(int argc, char *argv[]) {
	checkdb_exists();
	if (argc < 2) {
		explainer();
	} else if ((argc > 2) && (strcmp(argv[1],"--watch") == 0)) {
		watch_init(argc, argv);
	} else if ((strcmp(argv[1],"--backup-location") == 0)) {
		backup();
	} else {
		printf("- couldnt find %s command\n",argv[1]);
		explainer();
	}
}

void explainer(void) {
	printf("\033[34m No args were noted, available options include:\033[0m\n");
	printf("\033[34m    --watch location sets the location to be watched \n \ti.e ./updt --watch Documents\033[0m\n");
	printf("\033[34m    --unwatch removes watched location \n \t i.e ./updt --unwatch Documents\033[0m\n \t\033[31m cant be reversed and all config will be start from scratch\033[0m\n");
	printf("\033[34m    --backup-location chooses backup location \n \t i.e ./updt --backup-location \n");

}

void checkdb_exists(void) {
	struct stat pth, dpth;
	char path[] = "/home/brian/.updt";
	char db_path[] = "/home/brian/.updt/updt.db";

	if ((stat(path,&pth), 0) || (stat(db_path, &dpth),0)) {
		printf("Set up already");
	} else {
		db_init();
	}
}

void watch_init(int length, char *vec[]) {
	writeArgs(length, vec);	
	traverse_all();
}

// choose backup location
void backup(void) {
	write_prefered();
}
