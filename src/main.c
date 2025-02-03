#include <stdlib.h>
#include "entry.c"
#include <dirent.h>

int main(int argc, char *argv[]) {
	entrypoint(argc, argv);
	return EXIT_SUCCESS;
}
