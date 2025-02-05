/*
 * =====================================================================================
 *
 *       Filename:  db.h
 *
 *    Description:  handles sqlite3db stuff e.g creating necessary tables
 *        Version:  1.0
 *        Created:  01/27/2025 06:24:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BrianTum(), 
 *   Organization:  
 *
 * =====================================================================================
*/

#ifndef DB_H
#define DB_H

#include <sqlite3.h> 

// opens connection to db
sqlite3 *open_db(void);

// basic db functions that are needed
// including creating tables 
void db_init(void);
char *location(void);
void create_compfile_table(sqlite3 *conn);
void create_backuped_file_table(sqlite3 *conn);
void insert_compfiles(sqlite3 *conn,char *path, long int *date_modified, double size);
void insert_backup(sqlite3 *conn,char *path, long int *date_modified, double size);
void insert(sqlite3 *conn, char *tablename, char *path, long int *date_modified, double size);
// return count of watched path entries
int watched_paths(sqlite3 *conn);
#endif