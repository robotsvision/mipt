#ifndef STACK_H_
#define STACK_H_

/**************************************************************************//**
 * @file     stack.h
 * @brief    Stack. C version.
 * @version  V0.0.1
 * @date     24. Sep 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

// Pure C language requires
#ifndef __cplusplus

// C 2011 requires
#if __STDC_VERSION__  >= 201112L

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// @brief Stack key-value. / Handler.
typedef uint64_t stack_t;

void stack_init(stack_t* st);
void stack_deinit(stack_t* st);

void stack_push_char(stack_t* st, uint8_t data, bool sign);
void stack_push_short(stack_t* st, uint16_t data, bool sign);
void stack_push_int(stack_t* st, uint32_t data, bool sign);
void stack_push_long_long(stack_t* st, uint64_t data, bool sign);
void stack_push_ptr(stack_t* st, void* data);

void stack_pop(stack_t* st, void* data);

size_t stack_get_lenght();
size_t stack_get_size();

#else // C standard >= 2011
#   error "<stack.h> ERROR: C 2011 standard required."
#endif
#else // ! c++
#   error "<stack.h> ERROR: Use of C++ language is not permitted. Include 'stack.hpp' file instead."
#endif
#endif // STACK_H_
