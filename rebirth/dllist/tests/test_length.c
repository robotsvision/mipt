#include <stdio.h>
#include <assert.h>
#include "dllist.h"

void test_dllist_length_invalid_access() {
    dllist_t* list = dllist_create(10, sizeof(int));

    int result;
    dllist_get_element(list, -1, &result); 
    dllist_get_element(list, 1000, &result);

    printf("test_dllist_length_invalid_access passed\n");
    dllist_destroy(list);
}
