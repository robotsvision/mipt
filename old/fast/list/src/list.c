#include <list.h>

int list_create(list_t* new_list, size_t num_of_elements){
    if (num_of_elements == 0 || new_list == NULL)
        return -1;
    
    list_t list = (list_t){
        .elements = calloc(num_of_elements, sizeof(list_t)),
        .allocated = num_of_elements,
        .used = 0
    };

    if (list.elements == NULL)
        return -1;

    (*new_list) = list;
    return 0;
} 

int list_destroy(list_t* list){
    if (list == NULL || list->elements == NULL || list->allocated == 0UL)
        return -1;

    free(list->elements);

    (*list) = (list_t){
        .allocated = 0UL,
        .elements = NULL,
        .used = 0UL,
    };

    return 0;
}

sys_t list_get(list_t list, size_t n){
    if (list.used < n) {
        return -1;
    }
    node_t current_node = (*list.elements);
    for (size_t i = 0; i < n; ++i) {
        current_node = (current_node.next);
    }
    return current_node.value;
}

int list_push(list_t* list, sys_t new_element){

}

int list_pop(list_t* list, sys_t* new_element){

}

int list_insert_at(list_t* list, sys_t new_element, size_t n){

}

int list_remove_at(list_t* list, size_t n){

}