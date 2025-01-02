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

/* ========= General C implementation ========= */

#ifdef STACK_USE_CPP
#define _S_T(name) name
#define _S_L(name) name
namespace stack {
#else
#define _S_T(name) stack_##name##_t
#define _S_L(name) STACK_##name
#endif

// Stack headers
#include "errors.h"
#include "protection.h"
#include "system_info.h"

typedef enum {
    _S_L(ERROR_ALLOCATION),
    // ...
} _S_T(error);

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

/* ========= Class implementation ========= */

#ifdef STACK_USE_CPP
class container {
private:
    stack::handler _handler;
public:
    //stack::error create(size_t initial_size = );

};
#endif

#endif // STACK_H_
