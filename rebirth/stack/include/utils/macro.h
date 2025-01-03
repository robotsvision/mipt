
/**
 * @file utils/macro.h
 * @brief 
 * @version 3.0.0
 * @author Matvey Rybalkin
 */

#ifndef STACK_MACRO_H_
#define STACK_MACRO_H_

#ifdef STACK_USE_CPP
#   include <cassert>
#   include <cstddef>
#   include <stdatomic.h>
#else
#   include <assert.h>
#   include <stddef.h>
#   include <stdatomic.h>
#endif

#ifndef LIKELY
#   define LIKELY(x) __builtin_expect(!!(x), 1)
#endif

#ifndef UNLIKELY
#   define UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

#ifndef FORCE_INLINE
#   if defined(_MSC_VER)
#      define FORCE_INLINE __forceinline
#   elif defined(__GNUC__) || defined(__clang__)
#      define FORCE_INLINE inline __attribute__((always_inline))
#   else
#       define FORCE_INLINE inline
#   endif
#endif

#ifndef NO_INLINE
#   if defined(_MSC_VER)
#       define NO_INLINE __declspec(noinline)
#   else
#       define NO_INLINE __attribute__((noinline))
#   endif
#endif

#ifndef STATIC_ASSERT
#   define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#endif

#if  defined(_MSC_VER)
#    define PACKED_STRUCT(name) __pragma(pack(push, 1)) name __pragma(pack(pop))
#    define ALIGNED(x) __declspec(align(x))
#    define DEPRECATED __declspec(deprecated)
#elif defined(__GNUC__) || defined(__clang__)
#    define PACKED_STRUCT(name) name __attribute__((packed))
#    define ALIGNED(x) __attribute__((aligned(x)))
#    define DEPRECATED __attribute__((deprecated))
#endif


#endif // STACK_MACRO_H_
