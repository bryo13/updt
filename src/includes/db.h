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

#ifndef DB_H
#define DB_H

#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "store_location.h"

sqlite3 *open_db();
void db_init();
static char *location();
static void create_compfile_table(sqlite3 *conn);
static void create_backuped_file_table(sqlite3 *conn);
void insert_compfiles(sqlite3 *conn,char *path, long int *date_modified, double size);
void insert_backup(sqlite3 *conn,char *path, long int *date_modified, double size);
static void insert(sqlite3 *conn, char *tablename, char *path, long int *date_modified, double size);

void db_init() {
    sqlite3 *db_conn = open_db();
    create_compfile_table(db_conn);
    create_backuped_file_table(db_conn);
    sqlite3_close(db_conn);
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

    const char *table_sql = "CREATE TABLE IF NOT EXISTS compfilespaths(id integer PRIMARY KEY AUTOINCREMENT, path text UNIQUE, data_modified integer, size integer)";

    if (sqlite3_exec(db_conn, table_sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stdout, "Error opening db conn: %s\n", err_msg);
        return;
    }

}

// create backuped files
static void create_backuped_file_table(sqlite3 *db_conn) {
    char *err_msg = NULL;

    if (db_conn == NULL) {
        fprintf(stdout, "Error opening db conn: %s\n", sqlite3_errmsg(db_conn));
        return;
    }

    const char *table_sql = "CREATE TABLE IF NOT EXISTS backedfiles(id integer PRIMARY KEY AUTOINCREMENT, path text UNIQUE, data_modified integer, size integerma)";

    if (sqlite3_exec(db_conn, table_sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stdout, "Error opening db conn: %s\n", err_msg);
        return;
    }

}

// insert into compfiles table
void insert_compfiles(sqlite3 *conn,char *path, long int *date_modified, double size) {
	insert(conn,"compfilespaths",path, date_modified, size);
}

// insert into backup table
void insert_backup(sqlite3 *conn,char *path, long int *date_modified, double size) {
	insert(conn,"backedfiles",path, date_modified, size);
}

// insrt helper function
static void insert(sqlite3 *conn,char *tablename, char *path, long int *date_modified, double size) {
	sqlite3_stmt *stmt;
	int query_result = 0;
	char *insertSql = (char*)malloc(1024 * sizeof(char));
	if (insertSql == NULL) {
		perror("error alloc insert sql mem");
		return;
	}

	char makeQuery[1024];
	snprintf(makeQuery, sizeof(makeQuery), "INSERT INTO %s (path, data_modified, size) values(?,?,?);", tablename);
	query_result = sqlite3_prepare_v2(conn, makeQuery, -1, &stmt, NULL);
	if (query_result != SQLITE_OK) {
		fprintf(stdout, "error prep insert query: %s\n",sqlite3_errmsg(conn));
		sqlite3_close(conn);
		return;
	}

	// bind params
	sqlite3_bind_text(stmt, 1, path, -1, SQLITE_STATIC);
	sqlite3_bind_int64(stmt, 2, (__int64_t)date_modified);
	sqlite3_bind_int64(stmt, 3, size);

	// exec
	// query_result = sqlite3_step(stmt);
	//if (query_result != SQLITE_OK) {
	//	fprintf(stdout, "error inserting: %s\n",sqlite3_errmsg(conn));
	//	sqlite3_close(conn);
	//	return;
	//}
    while (sqlite3_step(stmt) == SQLITE_OK) {
        printf("inserting\n");
    }
	
    sqlite3_reset(stmt);
	sqlite3_finalize(stmt);
}

// db location
static char *location() {
    const char *dbpath = create_location();
    if (dbpath == NULL) {
		perror("err getting home path");
		exit(2);
	}
    char *db_location = (char *)malloc(strlen(dbpath) + 13);
    if (db_location == NULL) {
        perror("Error allocating db store path str");
        exit(2);
    }
    strcpy(db_location, dbpath);
    strcat(db_location, "/updt.db");

    return db_location;
}

static int watched_paths(sqlite3 *conn) {
    int rc = 0;
    int count = 0;
    sqlite3_stmt *stmt;
    const char *count_sql = "SELECT COUNT(id) FROM compfilespaths;";

    if (conn == NULL) {
        perror("Error connecting to db");
        return 2;
    }

    rc = sqlite3_prepare_v2(conn, count_sql,-1,&stmt,0);
    if (rc != SQLITE_OK) {
        fprintf(stdout, "error prep count sql: %s", sqlite3_errmsg(conn));
        return 2;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count;
    }
    return 2;
}

#endif