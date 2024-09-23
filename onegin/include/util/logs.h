#ifndef ONEGIN_UTIL_ASSERT_H_
#define ONEGIN_UTIL_ASSERT_H_

/**************************************************************************//**
 * @file     logs.h
 * @brief    Onegin App. Util / Asserts macroses and functions.
 * @version  V0.0.1
 * @date     12. Sep 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t onegin_log_level_t;

#define ONEGIN_LOG_LEVEL_DISABLE   0x00
#define ONEGIN_LOG_LEVEL_1         0x01
#define ONEGIN_LOG_LEVEL_2         0x02
#define ONEGIN_LOG_LEVEL_3         0x03
#define ONEGIN_LOG_LEVEL_ALL       0xFF

extern void onegin_log_stdout_init(onegin_log_level_t level);
extern void onegin_log_finit(const char* filename, onegin_log_level_t level);
extern void onegin_log_deinit(void);

extern void onegin_log(onegin_log_level_t level, const char* format, ...);

#ifdef DEBUG

#   include <stdio.h>
#   include <stdlib.h>

    extern FILE* _onegin_log_file;
    extern uint8_t _onegin_log_level;

#endif

#endif // ONEGIN_UTIL_ASSERT_H_