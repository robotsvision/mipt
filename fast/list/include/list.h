#ifndef LIST_H_
#define LIST_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int64_t sys_t;

typedef struct {
    sys_t value;
    node_t* next;
    node_t* prev;
} node_t;

typedef struct {
    node_t* elements;
    size_t allocated;
    size_t used;
} list_t;

extern int list_create(list_t* new_list, size_t num_of_elements); 
extern int list_destroy(list_t* list);

extern sys_t list_get(list_t list, size_t n);

extern int list_push(list_t* list, sys_t new_element);
extern int list_pop(list_t* list, sys_t* new_element);

extern int list_insert_at(list_t* list, sys_t new_element, size_t n);
extern int list_remove_at(list_t* list, size_t n);

#endif // LIST_H_