#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

// returns home dir
char *homepath() {
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

// will host data file in home dir
char *create_location() {
    char *home = (char*)malloc(10 * sizeof(char));
    home = homepath();
    char path[] = "/.updt";
    strcat(home, path);

    struct stat sbuf;
    if (stat(home, &sbuf) == 0) {
    	return home;
    }
    
    if (mkdir(home, 0755) == 0){
        return home;
    }
}
