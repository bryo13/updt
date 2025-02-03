/*
 * =====================================================================================
 *
 *       Filename:  tests.c
 *
 *    Description: tests c files in this project
 *                 uses criterion
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

#include <criterion/criterion.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "../src/includes/source_location.h"
#include "../src/includes/db.h"
#include "../src/watch_args.c"
#include "../src/compare.c"

// test homepath
Test(store_location, TestHomeDir) {
	const char *homePath = homepath();
	cr_assert_str_eq(homePath, "/home/brian");
}

Test(store_location, TestMakeDir) {
	struct stat sbuf;
	create_location();
	char path[] = "/home/brian/.updt";

	bool dirExists = stat(path, &sbuf);
	cr_assert_eq(dirExists, 0, "%s does not exist", path);
}

Test(db, CreateDB) {
	struct stat sbuf;
	db_init();
	char db_path[] = "/home/brian/.updt/updt.db";
	bool dbExists = stat(db_path, &sbuf);
	cr_assert_eq(dbExists, 0, "%s does not exist", db_path);
}

Test(compare, StripPath) {
	char *path = "/media/brian/Documents";
	char *path1 = "/home/brian/Documents";
	char *get_striped1 = strip_path(path);
	char *get_striped2 = strip_path(path1);
	cr_assert_not_null(get_striped1);
	cr_assert_not_null(get_striped2);

	cr_assert_str_eq(get_striped1,"/Documents","Couldnt get unmatched");
	cr_assert_str_eq(get_striped2,"/Documents","Couldnt get unmatched");
}

Test(compare, Traverse) {
	char *location = "/media/brian/BriansAge";
	char **paths = traverse(location);
	cr_assert_not_null(paths, " paths should contain subpaths");
	free(paths);
}

Test(compare, QueryEntries) {
	char **entries = query_entries();
	cr_assert_not_null(entries, " entries should contain subpaths");
	free(entries);
}