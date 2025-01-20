#include <criterion/criterion.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "../src/store_location.c"

// test homepath
Test(store_location, TestHomeDir) {
	char* homePath = homepath();
	cr_assert_str_eq(homePath, "/home/brian");
}

Test(store_location, TestMakeDir) {
	struct stat sbuf;
	create_location();
	char path[31] = "/home/brian/.updt";

	bool dirExists = stat(path, &sbuf);
	cr_assert_eq(dirExists, 0, "%s does not exist",path);

}
