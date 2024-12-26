
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
    
    size_t allocation_size = initial_size;
    if (initial_size == STACK_DEFAULT_ALLOCATION) {
        _get_page_size();
        allocation_size = _page_size;
    }

    stack_t* new_stack = calloc(1, sizeof(stack_t));

    if (new_stack == NULL)
        return NULL;

    new_stack->meta.allocated = allocation_size / configuration.size_of_element;
    new_stack->meta.top_index = 0;
    new_stack->configuration = configuration;

    if (new_stack->meta.allocated == 0) {
        free(new_stack);
        return NULL; 
    }

    void* stack_allocation = calloc(allocation_size, 1);

    if (stack_allocation == NULL) {
        free(new_stack);
        return NULL;
    }

    switch (configuration.size_of_element) {
        case (1UL):
            new_stack->content.data_8bit = (uint8_t*)stack_allocation;
            break;

        case (2UL):
            new_stack->content.data_16bit = (uint16_t*)stack_allocation;
            break;

        case (4UL):
            new_stack->content.data_32bit = (uint32_t*)stack_allocation;
            break;

        case (8UL):
            new_stack->content.data_64bit = (uint64_t*)stack_allocation;
            break;

#   if (__SIZEOF_DOUBLE__ != 8UL)
        case (sizeof(double)):
            new_stack->content.data_double = (double*)stack_allocation;
            break;
#   endif

        case (sizeof(long double)):
            new_stack->content.data_long_double = (long double*)stack_allocation;
            break;

        default: {
            free(new_stack);
            free(stack_allocation);
            return NULL;
        }
    }

    return new_stack;
}

void stack_destroy(stack_t* stack) {
    switch (stack->configuration.size_of_element) {
        case (1UL):
            free(stack->content.data_8bit);
            break;

        case (2UL):
            free(stack->content.data_16bit);
            break;

        case (4UL):
            free(stack->content.data_32bit);
            break;

        case (8UL):
            free(stack->content.data_64bit);
            break;

#   if (__SIZEOF_DOUBLE__ != 8UL)
        case (sizeof(double)):
            free(stack->content.data_double);
            break;
#   endif

        case (sizeof(long double)):
            free(stack->content.data_long_double);
            break;

        default: {
            __builtin_unreachable();
        }
    }
    free(stack);
}

/*
bool stack_push(stack_t* stack, void* new_element) {

    size_t element_index = stack->meta.mem_used;

    switch (stack->configuration.size_of_element) {
        case (1UL):
            *(stack->content.data_8bit + stack->meta.mem_used) = *(uint8_t*)(new_element);
            break;

        case (2UL):
            *(stack->content.data_16bit + stack->meta.mem_used) = *(uint16_t*)(new_element);
            break;

        case (4UL):
            *(stack->content.data_32bit + stack->meta.mem_used) = *(uint32_t*)(new_element);
            break;

        case (8UL):
            *(stack->content.data_64bit + stack->meta.mem_used) = *(uint64_t*)(new_element);
            break;

#   if (__SIZEOF_DOUBLE__ != 8UL)
        case (sizeof(double)):
            *(stack->content.data_double + stack->meta.mem_used) = *(double*)(new_element);
            break;
#   endif

        case (sizeof(long double)):
            *(stack->content.data_long_double + stack->meta.mem_used) = *(long double*)(new_element);
            break;

        default: {
            __builtin_unreachable();
    }
    

    return false;
}
*/


bool stack_pop(stack_t* stack, void* popped_element) {
    return false;
}

bool stack_peek(stack_t* stack, void* peeked_element) {
    return false;
}

size_t stack_get_size(stack_t* stack) {
    return (stack->meta.top_index * stack->configuration.size_of_element);
}

size_t stack_get_capacity(stack_t* stack) {
    return (stack->meta.allocated * stack->configuration.size_of_element);
}
