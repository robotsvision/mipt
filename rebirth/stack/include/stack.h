
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
// size_t is a keyword.
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

} _S_T(errors);

typedef struct {

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
