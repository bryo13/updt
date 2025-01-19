#include <criterion/criterion.h>
#include "../src/store_location.c"

// test homepath
Test(store_location, TestHomeDir) {
	char* homePath = homepath();
	cr_assert_str_eq(homePath, "/home/brian");
}

Test(store_location, TestMakeDir) {
	cr_assert_neq(create_location(), " ", "Should not return empty string but /home/brian/.updt");
}
