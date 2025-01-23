/*
 * =====================================================================================
 *
 *       Filename:  data.c
 *
 *    Description: create sqlite tables that store file path in selected
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
#include "./includes/store_location.h"

sqlite3 *open_db();
void db_init();
static char *location();
static void create_compfile_table(sqlite3 *conn);
static void create_backuped_file_table(sqlite3 *conn);

void db_init() {
    sqlite3 *dbConn = open_db();
    create_compfile_table(dbConn);
    create_backuped_file_table(dbConn);
}

sqlite3 *open_db() {
    char *lc = location();
    sqlite3 *db = NULL;

    if (sqlite3_open(lc, &db) != SQLITE_OK) {
        fprintf(stdout, "Error opening db conn: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    printf("connection est.\n");
    free(lc);
    return db;
}

// create hosts' files table to be monitored
static void create_compfile_table(sqlite3 *db_conn) {
    char *err_msg = NULL;

    if (db_conn == NULL) {
        fprintf(stdout, "Error opening db conn: %s\n", sqlite3_errmsg(db_conn));
        return;
    }

    const char *table_sql = "CREATE TABLE IF NOT EXISTS compfilespaths('id integer PRIMARY KEY AUTOINCREMENT, path text, data_modified integer')";

    if (sqlite3_exec(db_conn, table_sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stdout, "Error opening db conn: %s\n", err_msg);
        return;
    }
    printf("connected");
    sqlite3_close(db_conn);
}

// create backuped files
static void create_backuped_file_table(sqlite3 *db_conn) {
        char *err_msg = NULL;

    if (db_conn == NULL) {
        fprintf(stdout, "Error opening db conn: %s\n", sqlite3_errmsg(db_conn));
        return;
    }

    const char *table_sql = "CREATE TABLE IF NOT EXISTS backedfiles('id integer PRIMARY KEY AUTOINCREMENT, path text, data_modified integer')";

    if (sqlite3_exec(db_conn, table_sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stdout, "Error opening db conn: %s\n", err_msg);
        return;
    }
    printf("connected");
    sqlite3_close(db_conn);
}

// db lcoation
static char *location() {
    const char *dbpath = create_location();
    char *db_location = (char *)malloc(strlen(dbpath) + 10);
    if (db_location == NULL)
    {
        perror("Error allocating db store path str");
        exit(2);
    }
    strcpy(db_location, dbpath);
    strcat(db_location, "/updt.db");
    return db_location;
}
