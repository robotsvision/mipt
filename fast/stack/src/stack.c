#include <stack.h>

// PRIVATE FUNCTIONS

#if defined(WIN32)
#   include <windows.h>
#elif defined(__linux__)
#   include <unistd.h>
#else
#   warning "The operating system is not defined or is not supported."
#endif 

static size_t _page_size = 0UL;

static void _get_page_size(void) {
    if (_page_size == 0UL) {
#if defined(WIN32)
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        _page_size = (size_t)(si.dwPageSize);
#elif defined(__linux__)
        _page_size = (size_t)(sysconf(_SC_PAGESIZE));
#else
        _page_size = 4096UL;
#endif
    }
}

// PUBLIC FUNCTIONS

stack_error_t stack_create(stack_t* new_stack, size_t size_of_element) {
    if (new_stack == NULL || size_of_element == 0 || size_of_element > sizeof(int64_t)){
        return STACK_ERROR;
    }

    stack_t new_stack = (stack_t){

    };
}

stack_error_t stack_destroy(stack_t* new_stack);

