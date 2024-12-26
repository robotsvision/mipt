#include <stdio.h>
#include <assert.h>
#include "dllist.h"

void test_dllist_is_empty() {
    dllist_t* list = dllist_create(10, sizeof(int));
    assert(dllist_is_empty(list) == true);

    int value = 42;
    dllist_push_back(list, &value);
    assert(dllist_is_empty(list) == false);

    dllist_destroy(list);
    printf("test_dllist_is_empty passed\n");
}
