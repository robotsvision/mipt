#include <stdio.h>
#include <assert.h>
#include "dllist.h"

void test_dllist_create_invalid() {
    dllist_t* list = dllist_create(0, sizeof(int));
    assert(list == NULL);

    list = dllist_create(10, 0);
    assert(list == NULL);

    printf("test_dllist_create_invalid passed\n");
}

void test_dllist_destroy_null() {
    dllist_destroy(NULL);
    printf("test_dllist_destroy_null passed\n");
}