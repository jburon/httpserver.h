add_executable(test_fuzz_util test_fuzz_util.c ../fuzz_util.c)
target_include_directories(test_fuzz_util PRIVATE ..)
add_test(test_fuzz_util test_fuzz_util)

#request main is a manual test tool, not a unit test case
add_executable(fuzz_cli fuzz_cli.c ../fuzz_request.c ../fuzz_util.c)