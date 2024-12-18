#include <stdio.h>
#include <stdlib.h>

void test_dllist_create_destroy();
void test_dllist_is_empty();
void test_dllist_push_pop();
void test_dllist_memory_management();
void test_dllist_length_invalid_access();

void run_test(const char* test_name, void (*test_func)()) {
    printf("Running test: %s... ", test_name);
    test_func();
    printf("PASSED\n");
}

int main() {
    run_test("test_dllist_create_destroy", test_dllist_create_destroy);
    run_test("test_dllist_is_empty", test_dllist_is_empty);
    run_test("test_dllist_push_pop", test_dllist_push_pop);
    run_test("test_dllist_memory_management", test_dllist_memory_management);
    run_test("test_dllist_length_invalid_access", test_dllist_length_invalid_access);

    printf("All tests completed successfully.\n");
    return 0;
}
