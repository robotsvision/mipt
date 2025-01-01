
/**
 * @file system_info.hpp
 * @brief 
 * @version 3.0.0
 * @author Matvey Rybalkin
 */

#ifndef STACK_SYSTEM_INFO_H_
#define STACK_SYSTEM_INFO_H_

#ifdef __cplusplus
#   include <cassert>
#else
#   include <assert.h>
#endif

#ifndef LIKELY
    #define LIKELY(x) __builtin_expect(!!(x), 1)
#endif

#ifndef UNLIKELY
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

#ifndef FORCE_INLINE
    #if defined(_MSC_VER)
        #define FORCE_INLINE __forceinline
    #else
        #define FORCE_INLINE __attribute__((always_inline)) inline
    #endif
#endif

#ifndef NO_INLINE
    #if defined(_MSC_VER)
        #define NO_INLINE __declspec(noinline)
    #else
        #define NO_INLINE __attribute__((noinline))
    #endif
#endif

#ifndef STATIC_ASSERT
    #define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#endif

#endif // STACK_SYSTEM_INFO_H_
