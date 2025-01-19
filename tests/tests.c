#include <criterion/criterion.h>
#include "../src/homedir.c"

// test homepath
Test(homedir, TestHomeDir) {
	char* homePath = homepath();
	cr_assert_str_eq(homePath, "/home/brian");
}
