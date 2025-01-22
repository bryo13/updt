/*
 * =====================================================================================
 *
 *       Filename:  watchLocations.c
 *
 *    Description: The dir one wants to watch, the files and sub dir are stored in sqlite
 *    		        table as paths
 *        Version:  1.0
 *        Created:  01/22/2025 10:17:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

// read watch file
// returns array with paths to traverse
char **returnPath()
{
    char **path = (char *)malloc(16384 * sizeof(char));
    return path;
}

// traverse file system
// gets input from returnPath()
// save in db
void traverse(char **paths)
{
    DIR *dir;
    struct dirent entry;
    int len = sizeof(paths) / sizeof(paths[0]);
    for (int i = 0; i < len; i++)
    {
        if (!(dir = opendir(paths[i])))
        {
            return;
        }
    }
}
