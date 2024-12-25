#include <stdio.h>
#include <assert.h>
#include "dllist.h"

void test_dllist_push_pop_empty() {
    dllist_t* list = dllist_create(10, sizeof(int));

    int result;
    dllist_pop_back(list, &result);
    printf("test_dllist_push_pop_empty passed\n");
    dllist_destroy(list);
}

void test_dllist_push_pop_large() {
    dllist_t* list = dllist_create(100001, sizeof(int));
    int value = 42;

    for (int i = 0; i < 100; ++i) {
        dllist_push_back(list, &value);
    }

    for (int i = 0; i < 100; ++i) {
        int result;
        dllist_pop_back(list, &result);
        assert(result == 42);
    }

    assert(dllist_is_empty(list) == true);
    printf("test_dllist_push_pop_large passed\n");
    dllist_destroy(list);
}