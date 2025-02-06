#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include "backup_files.h"
#include "entry.h"

int main(int argc, char *argv[]) {
	entrypoint(argc, argv);
	return EXIT_SUCCESS;
}
