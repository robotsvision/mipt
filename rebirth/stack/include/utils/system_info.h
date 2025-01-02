
/**
 * @file system_info.h
 * @brief 
 * @version 3.0.0
 * @author Matvey Rybalkin
 */

#ifndef STACK_SYSTEM_INFO_H_
#define STACK_SYSTEM_INFO_H_

#ifdef STACK_USE_CPP
#   include <cstddef>
#   include <stdatomic.h>
#else
#   include <stddef.h>
#   include <stdatomic.h>
#endif

#define SYSINFO_MEMPAGE_DEFAULT 4096UL
extern atomic_size_t _sysinfo_mempage_size;
extern void sysinfo_mempage_update(void);

#endif // STACK_SYSTEM_INFO_H_
