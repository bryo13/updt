/*
 * =====================================================================================
 *
 *       Filename:  dest_location.h
 *
 *    Description: returns chosen location from a potential list 
 *			reads from /media/brian in my sys
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

#ifndef DEST_LOCATION_H
#define DEST_LOCATION_H

// returns array including backup locations i.e flash drives etc
char **backup_locations(void);

// selecting location user wants
char *prefered(void);

// noting prefered location
void write_prefered(void);

// helper fn that returns remaining size of a backup location
void remaining(char *path);

#endif