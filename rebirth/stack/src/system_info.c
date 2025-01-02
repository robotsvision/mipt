/*
    Supported OSs:
        1. Windows
        2. Linux
*/


#include <system_info.h>

/* ========= Operating system list ========= */

#define _SFI(x) #x
#define _S(x) _SFI(x)
#define _OS_SUPPORTED "Windows, Linux"// ...
#if !defined(WIN32) && !defined(__linux__) // ...
#   error "<system_info.h>: Unsupported operating system!"
#   pragma message("<system_info.h>:  Supported: " _S(_OS_SUPPORTED))
#endif
#undef _S
#undef _SFI

#ifdef WIN32
#   include <windows.h>
FORCE_INLINE size_t _get_mempage_size(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (size_t)(si.dwPageSize);
}
#endif

#ifdef __linux__
#   include <unistd.h>
// #   include <stdlib.h>
FORCE_INLINE size_t _get_mempage_size(void) {
    return (size_t)sysconf(_SC_PAGE_SIZE);
}
#endif

// etc..

/* ========= Cross-platform declaration ========= */

atomic_size_t _mempage_size = 0UL;

void sysinfo_mempage_update(void) {
    static size_t cached_size = 0UL;
    if (LIKELY(cached_size != 0UL)) {
        _mempage_size = cached_size;
        return;
    }
    size_t data = _get_mempage_size();
    atomic_store(&_mempage_size, data);
    cached_size = data;
}
