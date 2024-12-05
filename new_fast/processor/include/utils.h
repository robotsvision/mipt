#ifndef UTILS_H_
#define UTILS_H_

/**************************************************************************//**
 * @file     utils.h
 * @brief    Utility macros for common operations, including branch prediction 
 *           and logging.
 * @version  V1.0.0
 * @date     5. Dec 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#include <stdio.h>

/**
 * @brief Provides a hint to the compiler that a condition is likely true.
 * 
 * Use this macro to improve performance by informing the compiler that a 
 * condition is expected to evaluate to `true` most of the time.
 * 
 * @param x The condition to evaluate.
 * @return The value of `x`.
 */
#ifndef LIKELY
#  if defined(__GNUC__) || defined(__clang__)
#    define LIKELY(x)   __builtin_expect(!!(x), 1)
#  else
#    define LIKELY(x)   (x)
#  endif
#endif

/**
 * @brief Provides a hint to the compiler that a condition is unlikely true.
 * 
 * Use this macro to improve performance by informing the compiler that a 
 * condition is expected to evaluate to `false` most of the time.
 * 
 * @param x The condition to evaluate.
 * @return The value of `x`.
 */
#ifndef UNLIKELY
#  if defined(__GNUC__) || defined(__clang__)
#    define UNLIKELY(x) __builtin_expect(!!(x), 0)
#  else
#    define UNLIKELY(x) (x)
#  endif
#endif

/**
 * @brief Logs a message to the standard error stream.
 * 
 * Use this macro to log debug or error information. The message will include 
 * the source file name, line number, and a custom message.
 * 
 * @param fmt The format string (as in `printf`).
 * @param ... Additional arguments for the format string.
 */
#ifndef PROCESSOR_DEBUG_LOGS
#  define LOG(fmt, ...) \
    fprintf(stderr, "[LOG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define LOG(fmt, ...)
#endif

/**
 * @brief Logs an error message to the standard error stream.
 * 
 * Use this macro to log errors. The message will include the source file name, 
 * line number, and a custom message prefixed with `[ERROR]`.
 * 
 * @param fmt The format string (as in `printf`).
 * @param ... Additional arguments for the format string.
 */
#ifndef PROCESSOR_DEBUG_ERRORS
#  define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[ERROR] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define LOG_ERROR(fmt, ...)
#endif

#endif // UTILS_H_
