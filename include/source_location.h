/*
 * =====================================================================================
 *
 *       Filename:  store_location.c
 *
 *    Description: create a dir in the home dir that
 *                 will be used to house source config
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

#ifndef STORE_LOCATION_H
#define STORE_LOCATION_H

// returns home dir
const char *homepath(void);

// will host data file in home dir
const char *create_location(void);

// where to write pref location
const char *pref_loc(); 
#endif