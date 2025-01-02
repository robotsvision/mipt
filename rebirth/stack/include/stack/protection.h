




#ifndef STACK_PROTECTION_H_
#define STACK_PROTECTION_H_
#ifdef STACK_USE_CPP
#define _S_T(name) name
#define _S_L(name) name
namespace stack {
#else
#define _S_T(name) stack_##name##_t
#define _S_L(name) STACK_##name
#endif

typedef struct {

} _S_T(protect_conf);

#ifdef STACK_USE_CPP
}
#undef _S_T
#undef _S_L
#endif
#endif // STACK_PROTECTION_H_