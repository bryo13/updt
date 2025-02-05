/*
 * =====================================================================================
 *
 *       Filename:  entry.h
 *
 *    Description:  defined the entry point of the system. This is where the
 *                      user interracts with the program, including command line args
 * 
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

#ifndef ENTRY_H
#define ENTRY_H

/*
    explainer shows available commands or unknown commands
 */
void explainer(void);

// helper function that checks if a db is already created
void checkdb_exists(void);

// helper function that records dir/s one wants to watch for
// and records them
void watch_init(int length, char *vec[]);

// helps the user choose a backup location and notes it
void backup(void);

// user interactions handled here -> reception
void entrypoint(int argc, char *argv[]);

#endif