
/* ==================== Includes ==================== */

#include <dllist.h>
#include <stdlib.h>

/* ==================== Public functions ==================== */

dllist_t* dllist_create(size_t num_of_elements, size_t size_of_element) {

    if ((num_of_elements | size_of_element) == NULL)
        return NULL;

    dllist_t* new_dllist = calloc(1, sizeof(dllist_t));

    if (new_dllist == NULL)
        return NULL;

    void* elements_new_buffer = calloc(num_of_elements, size_of_element);

    if (elements_new_buffer == NULL) {
        free(new_dllist);
        return NULL;
    }

    switch (size_of_element) {
        case (1UL):
            new_dllist->content.list_elements.data_8bit = (uint8_t*)elements_new_buffer;
            break;

        case (2UL):
            new_dllist->content.list_elements.data_16bit = (uint16_t*)elements_new_buffer;
            break;

        case (4UL):
            new_dllist->content.list_elements.data_32bit = (uint32_t*)elements_new_buffer;
            break;

        case (8UL):
            new_dllist->content.list_elements.data_64bit = (uint64_t*)elements_new_buffer;
            break;

#   if (__SIZEOF_DOUBLE__ != 8UL)
        case (sizeof(double)):
            new_dllist->content.list_elements.data_double = (double*)elements_new_buffer;
            break;
#   endif

        case (sizeof(long double)):
            new_dllist->content.list_elements.data_long_double = (long double*)elements_new_buffer;
            break;

        default: {
            free(new_dllist);
            free(elements_new_buffer);
            return NULL;
        }
    }

    new_dllist->content.first_element = 0;
    new_dllist->content.next_elements = calloc(num_of_elements, sizeof(size_t));
    
    if (new_dllist->content.next_elements == NULL) {
        free(elements_new_buffer);
        free(new_dllist);
        return NULL;
    }
    
    new_dllist->content.prev_elements = calloc(num_of_elements, sizeof(size_t));

    if (new_dllist->content.prev_elements == NULL) {
        free(new_dllist->content.next_elements);
        free(elements_new_buffer);
        free(new_dllist);
        return NULL;
    }

    new_dllist->meta.last_index = 0;
    new_dllist->meta.num_of_elements = num_of_elements;
    new_dllist->size_of_element = size_of_element;

    return new_dllist;
}

void dllist_destroy(dllist_t* list) {
    switch (list->size_of_element) {
        case (1UL):
            free(list->content.list_elements.data_8bit);
            break;

        case (2UL):
            free(list->content.list_elements.data_16bit);
            break;

        case (4UL):
            free(list->content.list_elements.data_32bit);
            break;

        case (8UL):
            free(list->content.list_elements.data_64bit);
            break;

#   if (__SIZEOF_DOUBLE__ != 8UL)
        case (sizeof(double)):
            free(list->content.list_elements.data_double);
            break;
#   endif

        case (sizeof(long double)):
            free(list->content.list_elements.data_long_double);
            break;

        default: {
            __builtin_unreachable();
        }
    }
    free(list);
}

bool dllist_is_empty(dllist_t* list) {
    return (bool)(list->meta.last_index == 0);
}

size_t dllist_get_size_used_memory(dllist_t* list) {
    return (list->meta.num_of_elements * list->size_of_element);
}

size_t dllist_get_size_allocated_memory(dllist_t* list) {
}
size_t dllist_get_length(dllist_t* list);

void dllist_push_front(dllist_t* list, void* new_element);
void dllist_push_after(dllist_t* list, void* new_element);
void dllist_push_before(dllist_t* list, void* new_element);
void dllist_push_back(dllist_t* list, void* new_element);

void dllist_pop_front(dllist_t* list, void* dest_element);
void dllist_pop_n(dllist_t* list, void* new_element);
void dllist_pop_back(dllist_t* list, void* dest_element);

void dllist_get_element(dllist_t* list, size_t num_of_element, void* dest_element);
