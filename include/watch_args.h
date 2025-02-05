/*
 * =====================================================================================
 *
 *       Filename:  watch_args.h
 *
 *    Description:  args referes to arguments passed to --watch command
 *                      these are usually storage locations or dirs
 *                  if all conditions are meet, dir is present and not already watched
 *                      the new location is recorded
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

#ifndef WATCH_ARGS_H
#define WATCH_ARGS_H

// checks if the argument supplied corresponds to a valid path
int isPathValid(char *path);

// check if the arg supplied corresponds to a path aready watched
int isPathAlreadyWatched(char *path, char *fileLocation);

// notes dir/s to be watched
void writeArgs(int arg_count, char *argv[]);

#endif