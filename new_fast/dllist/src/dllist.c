
/* ==================== Includes ==================== */

#include <dllist.h>
#include <stdlib.h>
#include <string.h>

/* ==================== Private functions ==================== */

#define DLLIST_END ((size_t)-1)

static bool _is_valid_sizeof(size_t size_of_element) {
    return (bool)(
        size_of_element == sizeof(uint8_t)  ||
        size_of_element == sizeof(uint16_t) ||
        size_of_element == sizeof(uint32_t) ||
        size_of_element == sizeof(uint64_t) ||
        size_of_element == sizeof(double)   ||
        size_of_element == sizeof(long double)
    );
}

static void _free_resources(dllist_t* list, void* elements, size_t* next, size_t* prev) {
    if (list) free(list);
    if (elements) free(elements);
    if (next) free(next);
    if (prev) free(prev);
}

static size_t _get_index_by_position(dllist_t* list, size_t pos) {
    if (!list || pos >= list->meta.size) return DLLIST_END;
    size_t idx = list->content.first_element;
    for (size_t i = 0; i < pos && idx != DLLIST_END; i++) {
        idx = list->content.next_elements[idx];
    }
    return idx;
}

static size_t _get_last_index(dllist_t* list) {
    if (!list || list->content.first_element == DLLIST_END) return DLLIST_END;
    size_t idx = list->content.first_element;
    while (list->content.next_elements[idx] != DLLIST_END) {
        idx = list->content.next_elements[idx];
    }
    return idx;
}

/* ==================== Public functions ==================== */

dllist_t* dllist_create(size_t capacity, size_t element_size) {
    if ((capacity | element_size) == 0UL || capacity > SIZE_MAX / element_size)
        return NULL;

    dllist_t* new_dllist = calloc(1, sizeof(dllist_t));
    void* elements_new_buffer = calloc(capacity, element_size);
    size_t* next_buffer = calloc(capacity, sizeof(size_t));
    size_t* prev_buffer = calloc(capacity, sizeof(size_t));

    if (!new_dllist || !elements_new_buffer || !next_buffer || !prev_buffer) {
        _free_resources(new_dllist, elements_new_buffer, next_buffer, prev_buffer);
        return NULL;
    }

    switch (element_size) {
        case (1UL):
            new_dllist->content.elements.data_8bit = (uint8_t*)elements_new_buffer;
            break;
        case (2UL):
            new_dllist->content.elements.data_16bit = (uint16_t*)elements_new_buffer;
            break;
        case (4UL):
            new_dllist->content.elements.data_32bit = (uint32_t*)elements_new_buffer;
            break;
        case (8UL):
            new_dllist->content.elements.data_64bit = (uint64_t*)elements_new_buffer;
            break;
#   if (__SIZEOF_DOUBLE__ != 8UL)
        case (sizeof(double)):
            new_dllist->content.elements.data_double = (double*)elements_new_buffer;
            break;
#   endif
        case (sizeof(long double)):
            new_dllist->content.elements.data_long_double = (long double*)elements_new_buffer;
            break;
        default:
            _free_resources(new_dllist, elements_new_buffer, next_buffer, prev_buffer);
            return NULL;
    }

    new_dllist->content.first_element = DLLIST_END;
    new_dllist->content.next_elements = next_buffer;
    new_dllist->content.prev_elements = prev_buffer;

    // memset?
    for (size_t i = 0; i < capacity; i++) {
        new_dllist->content.next_elements[i] = DLLIST_END;
        new_dllist->content.prev_elements[i] = DLLIST_END;
    }

    new_dllist->meta.capacity = capacity;
    new_dllist->meta.size = 0;
    new_dllist->meta.last_used_index = DLLIST_END;

    return new_dllist;
}


void dllist_destroy(dllist_t* list) {
    if (!list) return;
    _free_resources(
        list, 
        list->content.elements.data_8bit, 
        list->content.next_elements, 
        list->content.prev_elements
    );
}

bool dllist_is_empty(dllist_t* list) {
    if (!list) return 0UL;
    return (bool)(list->meta.capacity == 0);
}

size_t dllist_get_size_used_memory(dllist_t* list) {
    if (!list) return 0UL;
    return (list->meta.capacity * list->element_size);
}

size_t dllist_get_size_allocated_memory(dllist_t* list) {
    if (!list) return 0UL;
    return (list->meta.size * list->element_size);
}

size_t dllist_get_length(dllist_t* list) {
    if (!list) return 0UL;
    return list->meta.capacity;
}

bool dllist_push_front(dllist_t* list, void* new_element) {
    if (!list 
    || !new_element 
    || !_is_valid_sizeof(list->element_size)) {
        return false;
    }

    if (list->meta.size >= list->meta.capacity) {
        return false; // No more space available
    }

    size_t new_index = list->meta.size;

    uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
    void* element_addr = base_addr + (new_index * list->element_size);
    memcpy(element_addr, new_element, list->element_size);

    list->content.next_elements[new_index] = list->content.first_element;
    list->content.prev_elements[new_index] = DLLIST_END;

    if (list->content.first_element != DLLIST_END) {
        list->content.prev_elements[list->content.first_element] = new_index;
    }

    list->content.first_element = new_index;
    list->meta.last_used_index = new_index;
    list->meta.size++;

    return true;
}

bool dllist_push_back(dllist_t* list, void* new_element) {
    if (!list 
    || !new_element 
    || !_is_valid_sizeof(list->element_size))
        return false;

    if (list->meta.size >= list->meta.capacity) {
        return false; // No space available
    }

    size_t new_index = list->meta.size;
    uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
    void* element_addr = base_addr + (new_index * list->element_size);
    memcpy(element_addr, new_element, list->element_size);

    if (list->content.first_element == DLLIST_END) {
        list->content.first_element = new_index;
        list->content.next_elements[new_index] = DLLIST_END;
        list->content.prev_elements[new_index] = DLLIST_END;
    } else {
        size_t last = _get_last_index(list);
        list->content.next_elements[last] = new_index;
        list->content.prev_elements[new_index] = last;
        list->content.next_elements[new_index] = DLLIST_END;
    }

    list->meta.size++;
    list->meta.last_used_index = new_index;
    return true;
}

bool dllist_push_after(dllist_t* list, size_t num_of_element, void* new_element) {
    if (!list 
    || !new_element 
    || !_is_valid_sizeof(list->element_size))
        return false;

    if (list->meta.size >= list->meta.capacity)
        return false;

    size_t current_index = _get_index_by_position(list, num_of_element);
    if (current_index == DLLIST_END) return false;

    size_t new_index = list->meta.size;
    uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
    void* element_addr = base_addr + (new_index * list->element_size);
    memcpy(element_addr, new_element, list->element_size);

    size_t next_idx = list->content.next_elements[current_index];
    list->content.next_elements[current_index] = new_index;
    list->content.prev_elements[new_index] = current_index;
    list->content.next_elements[new_index] = next_idx;
    if (next_idx != DLLIST_END) {
        list->content.prev_elements[next_idx] = new_index;
    }

    list->meta.size++;
    list->meta.last_used_index = new_index;
    return true;
}

bool dllist_push_before(dllist_t* list, size_t num_of_element,void* new_element) {
    if (!list 
    || !new_element 
    || !_is_valid_sizeof(list->element_size))
        return false;

    if (list->meta.size >= list->meta.capacity)
        return false;

    if (num_of_element == 0) {
        return dllist_push_front(list, new_element);
    }

    size_t current_index = _get_index_by_position(list, num_of_element);
    if (current_index == DLLIST_END) return false;

    size_t prev_idx = list->content.prev_elements[current_index];
    if (prev_idx == DLLIST_END) {
        return dllist_push_front(list, new_element);
    }

    size_t new_index = list->meta.size;
    uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
    void* element_addr = base_addr + (new_index * list->element_size);
    memcpy(element_addr, new_element, list->element_size);

    list->content.next_elements[prev_idx] = new_index;
    list->content.prev_elements[new_index] = prev_idx;
    list->content.next_elements[new_index] = current_index;
    list->content.prev_elements[current_index] = new_index;

    list->meta.size++;
    list->meta.last_used_index = new_index;

    return true;
}


bool dllist_pop_front(dllist_t* list, void* dest_element) {
    if (!list 
        || list->content.next_elements == NULL 
        || list->content.prev_elements == NULL 
        || list->content.elements.data_8bit == NULL 
        || list->content.first_element == DLLIST_END
        || !_is_valid_sizeof(list->element_size)) {
        return false;
    }

    if (list->meta.size == 0) {
        return false; 
    }

    size_t first_index = list->content.first_element;

    if (dest_element != NULL) {
        uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
        void* element_addr = base_addr + (first_index * list->element_size);
        memcpy(dest_element, element_addr, list->element_size);
    }

    size_t next_index = list->content.next_elements[first_index];
    list->content.first_element = next_index;

    if (next_index != DLLIST_END) {
        list->content.prev_elements[next_index] = DLLIST_END;
    }

    list->content.next_elements[first_index] = DLLIST_END;
    list->content.prev_elements[first_index] = DLLIST_END;

    list->meta.size--;
    if (list->meta.size == 0) {
        list->meta.last_used_index = DLLIST_END;
    }

    return true;
}

bool dllist_pop_back(dllist_t* list, void* dest_element) {
    if (!list 
        || list->content.next_elements == NULL 
        || list->content.prev_elements == NULL 
        || list->content.elements.data_8bit == NULL 
        || !_is_valid_sizeof(list->element_size)
        || list->meta.size == 0) {
        return false;
    }

    size_t last = _get_last_index(list);
    if (last == DLLIST_END) return false;

    if (dest_element != NULL) {
        uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
        void* element_addr = base_addr + (last * list->element_size);
        memcpy(dest_element, element_addr, list->element_size);
    }

    size_t prev_idx = list->content.prev_elements[last];
    if (prev_idx != DLLIST_END) {
        list->content.next_elements[prev_idx] = DLLIST_END;
    } else {
        list->content.first_element = DLLIST_END;
    }

    list->content.next_elements[last] = DLLIST_END;
    list->content.prev_elements[last] = DLLIST_END;

    list->meta.size--;
    if (list->meta.size == 0) {
        list->meta.last_used_index = DLLIST_END;
    }

    return true;
}

bool dllist_pop_after(dllist_t* list, size_t num_of_element, void* dest_element) {
    if (!list 
    || !_is_valid_sizeof(list->element_size) 
    || list->meta.size == 0)
        return false;

    size_t current_index = _get_index_by_position(list, num_of_element);
    if (current_index == DLLIST_END) return false;

    size_t to_remove = list->content.next_elements[current_index];
    if (to_remove == DLLIST_END) {
        return false;
    }

    if (dest_element != NULL) {
        uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
        void* element_addr = base_addr + (to_remove * list->element_size);
        memcpy(dest_element, element_addr, list->element_size);
    }

    size_t next_idx = list->content.next_elements[to_remove];
    list->content.next_elements[current_index] = next_idx;
    if (next_idx != DLLIST_END) {
        list->content.prev_elements[next_idx] = current_index;
    }

    list->content.next_elements[to_remove] = DLLIST_END;
    list->content.prev_elements[to_remove] = DLLIST_END;

    list->meta.size--;
    if (list->meta.size == 0) {
        list->meta.last_used_index = DLLIST_END;
    }

    return true;
}

bool dllist_pop_before(dllist_t* list, size_t num_of_element, void* dest_element) {
    if (!list 
    || !_is_valid_sizeof(list->element_size) 
    || list->meta.size == 0)
        return false;

    if (num_of_element == 0)
        return false;

    size_t current_index = _get_index_by_position(list, num_of_element);
    if (current_index == DLLIST_END) return false;

    size_t to_remove = list->content.prev_elements[current_index];
    if (to_remove == DLLIST_END) {
        return false;
    }

    if (dest_element != NULL) {
        uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
        void* element_addr = base_addr + (to_remove * list->element_size);
        memcpy(dest_element, element_addr, list->element_size);
    }

    size_t prev_idx = list->content.prev_elements[to_remove];
    list->content.next_elements[current_index] = list->content.next_elements[to_remove];

    if (prev_idx != DLLIST_END) {
        list->content.next_elements[prev_idx] = current_index;
    } else {
        list->content.first_element = current_index;
    }
    list->content.prev_elements[current_index] = prev_idx;

    list->content.next_elements[to_remove] = DLLIST_END;
    list->content.prev_elements[to_remove] = DLLIST_END;

    list->meta.size--;
    if (list->meta.size == 0) {
        list->meta.last_used_index = DLLIST_END;
    }

    return true;
}

bool dllist_get_element(dllist_t* list, size_t num_of_element, void* dest_element) {
    if (list == NULL 
    || dest_element == NULL 
    || num_of_element >= list->meta.size
    || list->content.next_elements == NULL
    || list->content.elements.data_8bit == NULL) {
        return false;
    }

    size_t current_index = _get_index_by_position(list, num_of_element);
    if (current_index == DLLIST_END) {
        return false;
    }

    if (!_is_valid_sizeof(list->element_size))
        return false;

    uint8_t* base_addr = (uint8_t*)list->content.elements.data_8bit;
    void* element_addr = base_addr + (current_index * list->element_size);

    memcpy(dest_element, element_addr, list->element_size);

    return true;
}
