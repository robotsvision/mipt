#ifndef ONEGIN_UTIL_TYPES_H_
#define ONEGIN_UTIL_TYPES_H_

/**************************************************************************//**
 * @file     flags.enum.h
 * @brief    Onegin App. Util / Basic types.
 * @version  V0.0.1
 * @date     17. Sep 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// UTF-8 types.
typedef uint32_t utf8_char_t;
typedef unsigned char* utf8_string_t;

// Cast

/// @brief 4 Byte character cast
#define UTF8_CHAR(char) (uint32_t)(char)

/// @brief UTF-8 strings cast
#define UTF8_CSTR(str) (utf8_string_t)(str)

/*************************************************************
 * Public
 ************************************************************/

/**
 * @brief Calculates lenght of the UTF-8 string.
 * 
 * @param[in] str string for calculation.
 * @returns the number of characters in string.
 */
extern size_t utf8_len(const utf8_string_t str);

/**
 * @brief Finds character in current string
 * 
 * @param[in] str string for calculation.
 * @param[in] ch character for search.
 * @returns position of the character in the string.
 */
extern int64_t utf8_find(const utf8_string_t str, utf8_char_t ch);

#endif // ONEGIN_UTIL_TYPES_H_