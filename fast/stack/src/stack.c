
/* ==================== Includes ==================== */

#include <stdlib.h>
#include <stack.h>

/* ==================== Private functions ==================== */

#if defined(WIN32)
#   include <windows.h>
#elif defined(__linux__)
#   include <unistd.h>
#else
#   warning "The operating system is not defined or is not supported."
#endif 

static size_t _page_size = 0UL; 

static __always_inline 
void _get_page_size(void) {
    if (_page_size == 0UL) {
#if defined(WIN32)
        static SYSTEM_INFO si;
        GetSystemInfo(&si);
        _page_size = (size_t)(si.dwPageSize);
#elif defined(__linux__)
        _page_size = (size_t)(sysconf(_SC_PAGESIZE));
#else
        _page_size = 4096UL;
#endif
    }
}


/* ==================== Public functions ==================== */

stack_t* stack_create(stack_conf_t configuration, size_t initial_size) {
    if (initial_size == STACK_DEFAULT_ALLOCATION) {
        _get_page_size();
        size_t allocation_size = _page_size;
    }

    stack_t* new_stack = calloc(1, sizeof(stack_t));

    // to be continured....
    return NULL;
}

void stack_destroy(stack_t* stack) {
    free(stack);
}


bool stack_push(stack_t* stack, void* new_element) {
    return false;
}

bool stack_pop(stack_t* stack, void* popped_element) {
    return false;
}
