#include <stdio.h>
#include <assert.h>
#include "dllist.h"

void test_dllist_memory_management() {
    dllist_t* list = dllist_create(10, sizeof(int));
    size_t initial_alloc = dllist_get_size_allocated_memory(list);
    size_t initial_used = dllist_get_size_used_memory(list);

    int value = 42;
    dllist_push_back(list, &value);
    assert(dllist_get_size_used_memory(list) > initial_used);

    int result;
    dllist_pop_back(list, &result);
    assert(dllist_get_size_used_memory(list) == initial_used);

    printf("test_dllist_memory_management passed\n");
    dllist_destroy(list);
}

