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
bool create_location() {
    // char *home = homepath();
    char *home = (char*)malloc(30 * sizeof(char));
    home = homepath();
    char path[30] = "/.updt";
    strcat(home, path);
    printf("%s\n",home);

    if (mkdir(home, 0755) == 0){
        return true;
    }

    return false;
}
