
/**
 * @file stack.h
 * @brief Dynamic stack implementation with additional safety and debug features.
 * 
 * This file contains the declarations for a flexible stack implementation,
 * supporting dynamic resizing, canary-based memory protection, and more.
 * 
 * @version 3.0.0
 * @date 12.12.24
 * @author Matvey Rybalkin
*/


#ifndef STACK_H_
#define STACK_H_

/* ==================== Includes ==================== */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ==================== Type definitions ==================== */

typedef enum {
    STACK_NO_HASH       = 0,
    STACK_HASH_CRC32    = 1,
    STACK_HASH_FNV      = 2,
    STACK_HASH_MURMUR3  = 3,
    STACK_HASH_JENKINS  = 4,
    STACK_HASH_BLAKE2   = 5,
    STACK_HASH_SHA3     = 6,
    STACK_HASH_SHA256   = 7,
} stack_function_type_t;

typedef struct {
    size_t size_of_element;
    struct {
        uint8_t use_canary           : 1;
        uint8_t hash_type            : 5;
        uint8_t use_hardware_protect : 1;
        uint8_t use_assert           : 1;
    } __attribute__((packed)) protection;
} stack_conf_t;

typedef struct {
    stack_conf_t configuration;
    struct {
        size_t top_index;
        size_t allocated;
    } meta;
    union {
        uint8_t*     data_8bit;
        uint16_t*    data_16bit;
        uint32_t*    data_32bit;
        uint64_t*    data_64bit;
        double*      data_double;
        long double* data_long_double;
    } content;
} stack_t;

#define STACK_DEFAULT_ALLOCATION 0UL

/* ==================== Public functions ==================== */

extern stack_t* stack_create(const stack_conf_t configuration, size_t initial_size);
extern void stack_destroy(stack_t* stack);

extern bool stack_push(stack_t* stack, void* new_element);
extern bool stack_pop(stack_t* stack, void* popped_element);
extern bool stack_peek(stack_t* stack, void* peeked_element);

extern size_t stack_get_size(stack_t* stack);
extern size_t stack_get_capacity(stack_t* stack);

#endif // STACK_H_
