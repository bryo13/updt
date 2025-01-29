/*
 * =====================================================================================
 *
 *       Filename:  compare.c
 *
 *    Description: compare tool for files watched and store location 
 *
 *        Version:  1.0
 *        Created:  01/24/2025 04:55:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Brian_Tum(), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stdio.h>

// strip location from path i.e /media/brian or /home/brian
char *strip_path(char *path) {
    regex_t regex;
    int res;
    char *pattern = "/media/brian|/home/brian";
    res = regcomp(&regex, pattern,REG_EXTENDED);
    if (res != 0) {
    	perror("couldnt compile re");
	return NULL;
    }

    regmatch_t match;
    res = regexec(&regex, path, 1, &match, 1);
    if (res == 0) {
    	int start = match.rm_so;
	int end = match.rm_eo;
	int len = end - start;

	char *unmatched = (char*)malloc(len + 1); 
	if (unmatched == NULL) {
		perror("error matched mem alloc");
		return NULL;
	}
	int char_to_cpy = strlen(path) - len;
	strncpy(unmatched, path + len, char_to_cpy);
	unmatched[char_to_cpy] = '\0';
	printf("matched %s\n",unmatched);
	return unmatched;
    }else if (res == REG_NOMATCH) {
    	printf("No match found\n");
	return NULL;
    } else {
    	printf("Err exec regex\n");
	return NULL;
    }
    regfree(&regex);
    return NULL;
}

// read dir from watched dir

// read dir in backup location

// compare 

// copy
