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

// Standard libraries
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*************************************************************
 * TYPES
 ************************************************************/

/**
 * @brief Stack structure.
 * 
 * Explanation:
 * 
 * The data in the stack buffer is stored in the format:
 * 
 * `[4 or 8 bytes][data from 1 to 8 bytes][1 byte]`
 * 
 * `[stack size (in bytes)][data][data type]`
 * 
 * `^----- void* sp` it's General stack pointer.
 * 
 * `sp + sizeof(size_t)` it's stack data.
 */
typedef struct {
    // General stack pointer
    void* sp; 
    // Dump fields of structure
#ifdef DEBUG
    // dump / current line of code
    uint64_t _line_of_code = 0;
    // dump / current function name
    char* _calling_function_name;
    // dump / current file name
    char* _file_name;
#endif
} stack_t;

// 
typedef enum {
    // Stack is OK
    STACK_OK                = 0x00,
    // Stack is Invalid (some errors with structure and data)
    STACK_INVALID           = 0x01,

    // Stack allocation error
    STACK_ERROR_ALLOC       = 0x02,
    // Stack freeing error
    STACK_ERROR_FREE        = 0x03,

    // Stack push operation types missmatch
    STACK_ERROR_TYPE_PUSH   = 0x04,
    // Stack pop operation types missmatch
    STACK_ERROR_TYPE_POP    = 0x05,

    // Stack overflow error
    STACK_ERROR_OVERFLOW    = STACK_ERROR_ALLOC,
    // Stack underflow error
    STACK_ERROR_UNDERFLOW   = 0x06,
} stack_error_t;

/**
 * @brief Explanation of `STACK_TYPE_`
 * 
 * `0b0011`
 * 
 * `----^^- last two bits set size of variable.`
 * 
 * `0b0100`
 * 
 * `---^- sign bit (1 -> unsigned, 0 -> signed)`
 * 
 * `0b1000`
 * 
 * `--^--- ptr bit (1 -> ptr, 0 -> data)`
 *  
 */

typedef uint8_t stack_data_type_t;

#define STACK_TYPE_CHAR         (stack_data_type_t)(1 << 0)
#define STACK_TYPE_SHORT        (stack_data_type_t)(1 << 1)
#define STACK_TYPE_INT          (stack_data_type_t)(1 << 2)
#define STACK_TYPE_LONG_LONG    (stack_data_type_t)(1 << 3)

#define STACK_TYPE_VALUE        (stack_data_type_t)(0 << 4)
#define STACK_TYPE_PTR          (stack_data_type_t)(1 << 4)

#define STACK_TYPE_SIGNED       (stack_data_type_t)(0 << 5)
#define STACK_TYPE_UNSIGNED     (stack_data_type_t)(1 << 5)

/*************************************************************
 * PUBLIC FUNCTIONS
 ************************************************************/

/** 
 * @brief To get the last error of all stacks. (errno like)
 */
extern stack_error_t stack_get_last_error(void);

/** 
 * @brief To get description of the last error.
 * 
 * For example:
 * 
 * `printf("%s", stack_get_last_error_cstr());`
 * 
 * @returns last error description
 */
extern const char* stack_get_last_error_cstr(void);

/** 
 * @brief To create a stack, and allocates memory.
 * 
 * @param[out] _s stack structure.
 */
extern stack_error_t stack_init(stack_t* _s);

/**
 * @brief To deinitialize stack, and free memory.
 * 
 * @param[in] _s stack structure.
 */
extern stack_error_t stack_deinit(stack_t* _s);

/**
 * @brief To get the tops' value type.
 * 
 * @param[in] _s stack structure.
 */
extern stack_data_type_t stack_get_top_type(stack_t* _s);

/*************************************************************
 * PRIVATE FUNCTIONS (FOR MACROSES)
 ************************************************************/

// PUSHES ***************************************************/

/**
 * @brief Private function to push one byte to the stack.
 * 
 * @param[out] _s stack pointer.
 * @param[in] _data data.
 * @param[in] _type type bit mask. (signed/unsigned)
 */
extern void _stack_push_1byte(stack_t* _s, uint8_t _data, bool _type);

/**
 * @brief Private function to push two bytes to the stack.
 * 
 * @param[out] _s stack pointer.
 * @param[in] _data data.
 * @param[in] _type type bit mask. (signed/unsigned)
 */
extern void _stack_push_2bytes(stack_t* _s, uint16_t _data, bool _type);

/**
 * @brief Private function to push four bytes to the stack.
 * 
 * @param[out] _s stack pointer.
 * @param[in] _data data.
 * @param[in] _type type bit mask. (signed/unsigned)
 */
extern void _stack_push_4bytes(stack_t* _s, uint32_t _data,  bool _type);

/**
 * @brief Private function to push eight bytes to the stack.
 * 
 * @param[out] _s stack pointer.
 * @param[in] _data data.
 * @param[in] _type type bit mask. (signed/unsigned)
 */
extern void _stack_push_8bytes(stack_t* _s, uint64_t _data, bool _type);

// POPS ***************************************************/


/**
 * @brief Private function to pop 1 byte of data from the stack.
 * 
 * @param[out] _s stack pointer.
 * @param[in] _data data pointer.
 * @param[in] _size size of current popped element.
 */
extern void _stack_pop(stack_t* _s, const void* restrict _data, size_t _size);


/*************************************************************
 * MACROSES
 ************************************************************/

#define STACK_PUSH(_s, _var, _type)    switch() \
                                        \
                                        \
                                        \
                                        \
                                        \
                                        \

#define STACK_POP(_s, _var, _type)      \
                                        \
                                        \
                                        \
                                        \
                                        \
                                        \

#else // C standard >= 2011
#   error "<stack.h> E#if __STDC_VERSION__  >= 201112LRROR: C 2011 standard required."
#endif
#else // ! c++
#   error "<stack.h> ERROR: Use of C++ language is not permitted. Include 'stack.hpp' file instead."
#endif
#endif // STACK_H_
