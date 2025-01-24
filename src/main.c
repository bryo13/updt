#include <stdlib.h>
#include "./includes/db.h"
#include "args.c"
#include "watchLocations.c"

int main(int argc, char *argv[]) {
    db_init();
    writeArgs(argc, argv);
    traverseAll();
}