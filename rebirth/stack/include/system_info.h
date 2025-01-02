
/**
 * @file system_info.h
 * @brief 
 * @version 3.0.0
 * @author Matvey Rybalkin
 */

#ifndef STACK_SYSTEM_INFO_H_
#define STACK_SYSTEM_INFO_H_

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

extern atomic_size_t _sysinfo_mempage_size;
extern void sysinfo_mempage_update(void);

#endif // STACK_SYSTEM_INFO_H_
