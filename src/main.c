#include <stdlib.h>
#include "db.c"
#include "args.c"

int main(int argc, char *argv[]) {
    create_db();
	writeArgs(argc, argv);
}