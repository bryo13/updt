/*
 * =====================================================================================
 *
 *       Filename:  backup_files.h
 *
 *    Description:  tracks files that need to be backed up
 *                      inserts into backup table
 *        Version:  1.0
 *        Created:  02/04/2025 06:24:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BrianTum(), 
 *   Organization:  
 *
 * =====================================================================================
*/

#ifndef BACKUP_FILES_H
#define BACKUP_FILES_H
#include <sqlite3.h>
#include <stdbool.h>


/*
remove prefex of watched location/s
to compare if remaining path is present or needs inserting
*/
char *remove_prefix(char *path);

/* 
traverse location only inserting watched dirs or files
*/
void traverse_backup(sqlite3 *conn, char *path, char *compare);

/*
return set-up backup location
*/
char *read_backup_location();

/*
return array with watch locations 
*/
char **watched();

/*
Check if watched locations are present in
backup location
*/
void check_all(void);
#endif
