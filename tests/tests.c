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
#include "../src/includes/store_location.h"
#include "../src/db.c"
#include "../src/args.c"

// test homepath
Test(store_location, TestHomeDir)
{
	const char *homePath = homepath();
	cr_assert_str_eq(homePath, "/home/brian");
}

Test(store_location, TestMakeDir)
{
	struct stat sbuf;
	create_location();
	char path[] = "/home/brian/.updt";

	bool dirExists = stat(path, &sbuf);
	cr_assert_eq(dirExists, 0, "%s does not exist", path);
}

Test(db, CreateDB)
{
	struct stat sbuf;
	create_db();
	char db_path[] = "/home/brian/.updt/updt.db";
	bool dbExists = stat(db_path, &sbuf);
	cr_assert_eq(dbExists, 0, "%s does not exist", db_path);
}
