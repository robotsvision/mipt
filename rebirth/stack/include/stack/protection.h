




#ifndef STACK_PROTECTION_H_
#define STACK_PROTECTION_H_

#include <utils/macro.h>

#ifdef STACK_USE_CPP
namespace protect {
#endif

typedef struct {
    uint8_t canary;
} PACKED_STRUCT(_S_T(_protect_, config));

typedef struct {

} _SP_T(meta);

#ifdef STACK_USE_CPP
}
#endif

#endif // STACK_PROTECTION_H_
