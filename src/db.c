/*
 * =====================================================================================
 *
 *       Filename:  data.c
 *
 *    Description: create sqite table that stores files in selected
 *                 location and backup location
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
#include <sqlite3.h>
#include <string.h>

#include "store_location.h"

void create_db() {
    char *dbpath = create_location();
    strcat(dbpath, "/updt.db");
    sqlite3 *db;

    if (sqlite3_open(dbpath, &db) != SQLITE_OK) {
        fprintf(stdout, "Error opening db conn: %s\n",sqlite3_errmsg(db));
        exit(2);
    } else {
        printf("connection est.\n");
    }
    sqlite3_close(db);
}