#include <stdio.h>
#include <stdlib.h>

extern void test_dllist_destroy_null();
extern void test_dllist_create_invalid();
extern void test_dllist_is_empty();
extern void test_dllist_push_pop_empty();
extern void test_dllist_push_pop_large();
extern void test_dllist_memory_management();
extern void test_dllist_length_invalid_access();

void run_test(const char* test_name, void (*test_func)()) {
    printf("Running test: %s... ", test_name);
    test_func();
    printf("PASSED\n");
}

int main() {
    run_test("test_dllist_destroy_null", test_dllist_destroy_null);
    run_test("test_dllist_create_invalid", test_dllist_create_invalid);
    run_test("test_dllist_is_empty", test_dllist_is_empty);
    run_test("test_dllist_push_pop", test_dllist_push_pop_empty);
    run_test("test_dllist_push_pop", test_dllist_push_pop_large);
    run_test("test_dllist_memory_management", test_dllist_memory_management);
    run_test("test_dllist_length_invalid_access", test_dllist_length_invalid_access);

    printf("All tests completed successfully.\n");
    return 0;
}
