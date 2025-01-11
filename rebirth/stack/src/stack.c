#include <stack.h>
#include <stdlib.h>
#include <stdbool.h>

#include <utils/macro.h>

/* ============= Private functions ============= */

bool _is_aligned_size(size_t size) {
    return (bool)!(size & 1);
}

bool _in_std_types_limit(size_t size) {
    return (size <= __SIZEOF_LONG_DOUBLE__);
}


/* ============= Public functions ============= */

stack_handler_t* stack_create(stack_config_t config) {
    if (config.size_of_element == 0UL || !_is_aligned_size(config.size_of_element))
        return NULL;
    stack_handler_t* new_handler = calloc(1, sizeof(stack_handler_t));
    if (!new_handler)
        return NULL;
    
    new_handler->content.data_unaligned = calloc(config.num_of_elements, config.size_of_element);
   
    if (!new_handler->content.data_unaligned) {
        free(new_handler);
        return NULL;
    }
   
    new_handler->meta.allocated = (config.num_of_elements * config.size_of_element);

}

void stack_destroy(stack_handler_t* stack);

stack_error_t stack_push(stack_handler_t* stack, void* new_element);
stack_error_t stack_pop(stack_handler_t* stack, void* popped_element);

char* stack_dump(stack_handler_t* stack);

size_t stack_get_state(stack_config_t* config);
bool stack_is_empty(stack_handler_t* stack);

const char* stack_str_error(stack_handler_t* handler) {
    return _stack_str_error(handler);
}

bool stack_fput_error(_STL(FILE*) stream, stack_handler_t* handler, const char* prefix) {
    const char* str_error = _stack_str_error(handler);
    if (!str_error)
        return false;
    return ( UNLIKELY(
        fputs(prefix, stream) == EOF|| 
        fputs(": ", stream) == EOF ||
        fputs(str_error, stream) == EOF
        )
    ) ? false : true;
}
