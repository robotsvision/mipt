
/**
 * @file stack.h
 * @brief 
 * @version 3.0.0
 * @author Matvey Rybalkin
 */

#if defined(STACK_USE_CPP) && !defined(__cplusplus)
#    error "You want to use the C++ version of the stack,\
 but the current compilation is for the C language."
#endif

#ifndef STACK_H_
#define STACK_H_

/* ========= Include headers ========= */

#ifdef STACK_USE_CPP
#   include <cstdint>
#   include <cstddef>
#   include <cstdio>
#else
#   include <stdint.h>
#   include <stdbool.h>
#   include <stdio.h>
#   include <stddef.h>
#endif

// Stack headers
#include "utils/macro.h"
#include "utils/system_info.h"

/* ========= General C implementation ========= */

#ifdef STACK_USE_CPP
#define _S_T(subname, name) name
#define _S_L(subname, name) name
#define _STL(type) std::##type
namespace stack {
#else
#define _S_T(subname,name) stack##subname##name##_t
#define _S_L(subname,name) STACK##subname##name
#define _STL(type) type
#endif

#include "stack/errors.h"
#include "stack/protection.h"

typedef enum {
    _S_L(_, ERROR_ALLOCATION),
    // ...
} _S_T(_, error);

typedef enum {
    _S_L(_, DEFAULT_NUMBER_OF_ELEMENTS),
} _S_T(_, num_of_elements);

typedef struct {
    size_t size_of_element;
    _S_T(_, num_of_elements) num_of_elements;
#ifdef STACK_USE_PROTECTION
    _S_T(_protect_, config) protect_config;
#endif
} _S_T(_, config);

typedef struct {
    size_t size;
    size_t allocated;
    size_t size_of_element;
} _S_T(_, state);

typedef struct {
    union {
        void* data_unaligned;
        uint8_t*  data_8bit;
        uint16_t* data_16bit;
        uint32_t* data_32bit;
        uint64_t* data_64bit;
#if __SIZEOF_DOUBLE__ != 8UL
        double*   data_double;
#endif
        long double* data_ldouble;
    } content;
    struct {
        size_t used;
        size_t allocated;
    } meta;
#ifdef STACK_USE_PROTECTION
    
#endif
} _S_T(_, handler);


#ifdef STACK_USE_CPP
}
#undef _S_T
#undef _S_L
#endif

#ifndef STACK_USE_CPP

/* ========= C version ========= */

stack_handler_t* stack_create(stack_config_t config);
void stack_destroy(stack_handler_t* stack);

stack_error_t stack_push(stack_handler_t* stack, void* new_element);
stack_error_t stack_pop(stack_handler_t* stack, void* popped_element);

char* stack_dump(stack_handler_t* stack);

size_t stack_get_state(stack_config_t* config);
bool stack_is_empty(stack_handler_t* stack);

const char* stack_str_error(stack_handler_t* handler);
void stack_fput_error(_STL(FILE*) stream, stack_handler_t* handler, const char* prefix);

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
    stack::handler create(size_t initial_size);
    stack::handler create(stack::config conf);

    void push(const T& element);
    T pop(void);

    bool is_empty(void);
    size_t get_state(stack::config* conf);

    size_t length(void);
    size_t size(void);

    const char* str_error(stack::handler handler);
    const char* str_error(std::ostream& stream, stack_handler_t* handler, const char* prefix = "");

    ~container();
};
}
#endif

#endif // STACK_H_
