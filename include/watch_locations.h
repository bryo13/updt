/*
 * =====================================================================================
 *
 *       Filename:  watch_locations.h
 *
 *    Description:  after supplying --watch with dirs one wants to watch
 *                      watch locations goes through them and records the files 
 *                      or subdirs therein
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

#ifndef WATCH_LOCATIONS_H
#define WATCH_LOCATIONS_H
#include <sqlite3.h>

// returns an array containing all paths one wants to watch
char **returnPath(void);

// gets individual paths from returnPath and loops them for files and subdir noting the files
void traverse_incompfiles(sqlite3 *conn, char *path);

// returns path to store watch locations
char *loc(void);

// does traverse_incompfiles for all locations supplied to --watch
void traverse_all(void);

#endif