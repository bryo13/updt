/*
* homedir returns a linux systems' home directory path
*
*/

#include <stdlib.h>
#include <stdio.h>

char* homepath() {
	char *homedir = NULL;
#ifdef __linux__
	homedir = getenv("HOME");
#else
	printf("Not linux system\n");
#endif
	if (homedir) {
		return homedir;
	} else {
		perror("Couldnt find getenv HOME\n");
	}
	return NULL;
}

