




#ifndef STACK_PROTECTION_H_
#define STACK_PROTECTION_H_

#include <utils/macro.h>

#ifdef STACK_USE_CPP
#define _SP_T(name) name
#define _SP_L(name) name
namespace stack {
namespace protection {
#else
#define _SP_T(name) stack_protect_##name##_t
#define _SP_L(name) STACK_PROTECT_##name
#endif

typedef struct {
    uint8_t canary : 1;
} PACKED_STRUCT(_SP_T(config));

typedef struct {

} _SP_T(meta);


#ifdef STACK_USE_CPP
} // protection::
} // stack::
#undef _SP_T
#undef _SP_L
#endif
#endif // STACK_PROTECTION_H_
