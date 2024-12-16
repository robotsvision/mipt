
/**
 * @file dllist.h
 * @brief Doubly linked list implementation.
 * 
 * @version 1.0.0
 * @date 15.12.24
 * @author Matvey Rybalkin
*/

#ifndef DLLIST_H_
#define DLLIST_H_

/* ==================== Includes ==================== */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ==================== Type definitions ==================== */

typedef struct {
    size_t size_of_element;
    struct {
        size_t num_of_elements;
        size_t last_index;
    } meta;

    struct {
        union {
            uint8_t*     data_8bit;
            uint16_t*    data_16bit;
            uint32_t*    data_32bit;
            uint64_t*    data_64bit;
            double*      data_double;
            long double* data_long_double;
        } list_elements;
        size_t first_element;
        size_t* next_elements;
        size_t* prev_elements;
    } content;
} dllist_t;

extern dllist_t* dllist_create(size_t num_of_elements, size_t size_of_element);
extern void dllist_destroy(dllist_t* list);
extern bool dllist_is_empty(dllist_t* list);

extern size_t dllist_get_size_used_memory(dllist_t* list);
extern size_t dllist_get_size_allocated_memory(dllist_t* list);
extern size_t dllist_get_length(dllist_t* list);

extern void dllist_push_front(dllist_t* list, void* new_element);
extern void dllist_push_back(dllist_t* list, void* new_element);

extern void dllist_pop_front(dllist_t* list, void* dest_element);
extern void dllist_pop_back(dllist_t* list, void* dest_element);

extern void dllist_get_element(dllist_t* list, size_t num_of_element, void* dest_element);

#endif // DLLIST_H_