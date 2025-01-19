#include <criterion/criterion.h>
#include "../src/store_location.c"

// test homepath
Test(store_location, TestHomeDir) {
	char* homePath = homepath();
	cr_assert_str_eq(homePath, "/home/brian");
}

Test(store_location, TestMakeDir) {
	cr_assert_eq(create_location(), 0, "Got %d wanted 0",create_location());
}
