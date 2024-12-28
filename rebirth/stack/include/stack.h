
/**
 * @file stack.h
 * @brief 
 * @version 3.0.0
 * @author Matvey Rybalkin
 */

#ifndef STACK_H_
#define STACK_H_

/* ========= Include headers ========= */

#ifdef __cplusplus
#   include <cstdint>
#   include <cstddef>
#   include 
#else
#   include <stdint.h>
#   include <stddef.h>
#endif

/* ========= General C implementation ========= */

#ifdef __cplusplus
#define _S_T(name) stack_##name##_t
#define _S_L(name) STACK_##name
namespace stack {
#else
#define _S_T(name) name
#define _S_L(name) name
#endif

// Stack headers
#include "errors.h"
#include "protection.h"

typedef enum {
    _S_L(ERROR_ALLOCATION),
    // ...
} _S_T(errors);

typedef struct {
    union {
        uint8_t* data_8bit;
        uint8_t* data_16bit;
        uint8_t* data_32bit;
        uint8_t* data_64bit;
        double* data_double;
        long double* data_ldouble;
    } content;
    struct {
        size_t used;
        size_t allocated;
    } meta;
    // for protection we should create struct.
} _S_T(handler);


#ifdef __cplusplus
}
#undef _S_T
#undef _S_L
#endif

/* ========= Class implementation ========= */

#ifdef __cplusplus
class stack {
private:
    
public:
};
#endif

#endif // STACK_H_
