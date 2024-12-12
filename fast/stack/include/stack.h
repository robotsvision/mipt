
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
        uint8_t hash                 : 5;
        uint8_t use_hardware_protect : 1;
        uint8_t use_assert           : 1;
    } __attribute__((packed)) protection;
} stack_conf_t;

typedef struct {
    stack_conf_t configuration;
    struct {
        size_t mem_used;
        size_t capacity;
    } meta;
    union {
        uint8_t*  u8_data;
        uint16_t* u16_data;
        uint32_t* u32_data;
        uint64_t* u64_data;
        float*    float_data;
        double*   double_data;
        long double* ldouble_data;
    } content;
} stack_t;

#define STACK_DEFAULT_ALLOCATION 0UL

/* ==================== Public functions ==================== */

stack_t* stack_create(const stack_conf_t configuration, size_t initial_size);
void stack_destroy(stack_t* stack);

bool stack_push(stack_t* stack, void* new_element);
bool stack_pop(stack_t* stack, void* popped_element);

#endif // STACK_H_
