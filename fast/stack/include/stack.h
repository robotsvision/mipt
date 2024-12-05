#ifndef STACK_H_
#define STACK_H_

#ifdef __cplusplus
#   error "This file is only allowed to be used in C language assembly. For C++ use stack.hpp file"
#endif

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief The maximum size of an operated type is limited 
 * by the maximum size of a type in the C language.
 */
#define STACK_ELEMENT_MAX_SIZE sizeof(int64_t)

#define STACK_INITIAL_SIZE 4096UL

/**
 * @typedef stack_element_t
 * @brief Stack element type.
 */
typedef int64_t stack_element_t;

/**
 * @typedef stack_error_t
 * @brief Stack function errors enumeration.
 */
typedef enum {
    STACK_OK        = 0x00,
    STACK_EXTENDED  = 0x01,
    STACK_ERROR     = 0x02,
} stack_error_t;

/**
 * @typedef stack_t
 * @brief The structure contains all the information 
 * about the stack, you can create and destroy the stack.
 */
typedef struct {
    void* data;             /**< */
    size_t sizeof_element;  /**< */
    size_t capacity;        /**< */
    size_t used;            /**< */
} stack_t;

stack_error_t stack_create(stack_t* new_stack, size_t size_of_element);
stack_error_t stack_destroy(stack_t* stack);

stack_error_t stack_push(stack_t* stack, void* element);
void* stack_pop(stack_t* stack);

#endif // STACK_H_
