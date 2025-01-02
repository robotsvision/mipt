#define STACK_USE_CPP
/**
 * @file stack.h
 * @brief 
 * @version 3.0.0
 * @author Matvey Rybalkin
 */

#ifdef STACK_USE_CPP
#   ifndef __cplusplus
#       error "You want to use the C++ version of the stack,\
 but the current compilation is for the C language."
#   endif
#endif

#ifndef STACK_H_
#define STACK_H_

/* ========= Include headers ========= */

#ifdef STACK_USE_CPP
#   include <cstdint>
#   include <cstddef>
#else
#   include <stdint.h>
#   include <stddef.h>
#endif

// Stack headers
#include "utils/macro.h"
#include "utils/system_info.h"
#include "stack/errors.h"
#include "stack/protection.h"

/* ========= General C implementation ========= */

#ifdef STACK_USE_CPP
#define _S_T(name) name
#define _S_L(name) name
namespace stack {
#else
#define _S_T(name) stack_##name##_t
#define _S_L(name) STACK_##name
#endif

typedef enum {
    _S_L(ERROR_ALLOCATION),
    // ...
} _S_T(error);

typedef struct {
    size_t size;
} _S_T(config);

typedef struct {
    size_t size;
} _S_T(state);

typedef struct {
    union {
        uint8_t*  data_8bit;
        uint16_t* data_16bit;
        uint32_t* data_32bit;
        uint64_t* data_64bit;
        double*   data_double;
        long double* data_ldouble;
    } content;
    struct {
        size_t used;
        size_t allocated;
    } meta;
    // for protection we should create struct.
} _S_T(handler);


#ifdef STACK_USE_CPP
}
#undef _S_T
#undef _S_L
#endif

#ifndef STACK_USE_CPP

/* ========= C version ========= */

stack_handler_t* stack_create(size_t num_of_elements, size_t size_of_element);
void stack_destroy(stack_handler_t* stack);

stack_error_t stack_push(stack_handler_t* stack, void* new_element);
stack_error_t stack_pop(stack_handler_t* stack, void* popped_element);

char* stack_dump(stack_handler_t* stack);

size_t stack_get_state(stack_config_t* config);
bool stack_is_empty(stack_handler_t* stack);

#else

/* ========= C++ version ========= */
namespace stack {
template <typename T>
class container {
private:
    stack::handler _handler;
public:
    container(void);
    container(size_t initial_size);
    stack::error create(size_t initial_size);
    stack::error create(stack::config conf);

    void push(const T& element);
    T pop(void);

    bool is_empty(void);
    size_t get_state(stack::config* conf);

    size_t length(void);
    size_t size(void);
};
}
#endif

#endif // STACK_H_
