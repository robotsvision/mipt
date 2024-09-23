#ifndef STACK_H_
#define STACK_H_

/**************************************************************************//**
 * @file     stack.h
 * @brief    MIPT project 3. Stack.
 * @version  V0.0.1
 * @date     20. Sep 2024
 * @author   Matvey Rybalkin
******************************************************************************/

// Standard libraries
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Macros to calculate number of arguments.
#define GET_NUM_ARGS(...) NUM_ARGS_IMPL(__VA_ARGS__, 100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,_100,N,...) N

/// @brief Stack datatypes
typedef enum {
    STACK_PTR_TYPE  = 0b1000,  // aka `any*`

    STACK_U8_TYPE   = 0b0000,  // aka `uint8_t`
    STACK_I8_TYPE   = 0b0001,  // aka `int8_t`
    STACK_CHAR_TYPE = 0b0001,  // aka `int8_t`

    STACK_U16_TYPE  = 0b0010, // aka `uint16_t`
    STACK_I16_TYPE  = 0b0011, // aka `int16_t`

    STACK_U32_TYPE  = 0b0100, // aka `uint32_t`
    STACK_I32_TYPE  = 0b0101, // aka `int32_t`

    STACK_U64_TYPE  = 0b0110, // aka `uint64_t`
    STACK_I64_TYPE  = 0b0111, // aka `int64_t`

} stack_data_type_t;

/// @brief Stack push/pop status
typedef enum {
    STACK_ALLOCATE_MEMORY_OK,
    STACK_ALLOCATE_MEMORY_ERROR,
    STACK_OK,
} stack_status_t;

/// @brief Stack main structure
typedef struct {
    size_t size;    // Size of the allocated memory for stack
    size_t rsize;   // Size of the used memory for stack
    void* sp;       // Stack data pointer.
} stack_t;

/*************************************************************
 * Private / Stack initialization
 ************************************************************/

/**
 * @brief Initialize stack, and allocate basic claster.
 * 
 */
extern int _stack_init(stack_t* stack);

/*************************************************************
 * Private / Stack pushes
 ************************************************************/

/**
 * @brief Add one byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be (unsigned) char, uint8_t or int8_t or a constant)
 * @param[out] type `STACK_U8_TYPE` or `STACK_I8_TYPE`
 * @returns 
 */
extern int _stack_push1   (
                    stack_t* stack,
                    const int8_t data, 
                    stack_data_type_t type
                    );

/**
 * @brief Add two byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be (unsigned) short, uint16_t or int16_t or a constant)
 * @param[out] type `STACK_U16_TYPE` or `STACK_I16_TYPE`
 * @returns `0` in success, or `-1` if an error occurs
 */
extern int _stack_push2   (
                    stack_t* stack, 
                    const int16_t data, 
                    stack_data_type_t type
                    );

/**
 * @brief Add four byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be (unsigned) int, uint32_t or int32_t or a constant)
 * @param[out] type `STACK_U32_TYPE` or `STACK_I32_TYPE`
 * @returns `0` in success, or `-1` if an error occurs
 */
extern int _stack_push4   (
                    stack_t* stack, 
                    int32_t data, 
                    stack_data_type_t type
                    );

/**
 * @brief Add eight byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be long long , uint64_t or int64_t or a constant)
 * @param[out] type `STACK_U64_TYPE` or `STACK_I64_TYPE`
 * @returns `0` in success, or `-1` if an error occurs
 */
extern int _stack_push8   (
                    stack_t* stack, 
                    const int64_t data, 
                    stack_data_type_t type
                    );

/**
 * @brief Add pointer for any data. 
 * 
 * @param[out] stack stack structure
 * @param[out] data data pointer
 * @param[out] type
 * @returns `0` in success, or `-1` if an error occurs
 */
extern int _stack_push_ptr(stack_t* stack, void* data, stack_data_type_t type);

/*************************************************************
 * Private / Stack pops
 ************************************************************/


/*************************************************************
 * Public / Stack macroses
 ************************************************************/

/**
 * @brief Creates and allocates 
 */
#define stack_init(stack)   _stack_init(stack)

/**
 * @brief Pushes and extends (if it's requred) stack buffer.
 * 
 * how to use:
 * ```
 * const char* my_string = "Hello Lena!";
 * stack_push(my_stack, my_string, STACK_CHAR_TYPE|STACK_PTR_TYPE);
 * ``` 
 */
#define stack_push(stack, data, type)   do {                                        \
                                            switch (type) {                         \
                                            case (STACK_PTR_TYPE):                  \
                                                _stack_push_ptr(stack, data, type);       \
                                            case (STACK_U8_TYPE):                   \
                                            case (STACK_I8_TYPE):                   \
                                                _stack_push1(stack, data, type);    \
                                            case (STACK_U16_TYPE):                  \
                                            case (STACK_I16_TYPE):                  \
                                                _stack_push2(stack, data, type);    \
                                            case (STACK_U32_TYPE):                  \
                                            case (STACK_I32_TYPE):                  \
                                                _stack_push3(stack, data, type);    \
                                            case (STACK_U64_TYPE):                  \
                                            case (STACK_I64_TYPE):                  \
                                                _stack_push4(stack, data, type);    \
                                            }\
                                        } while(0)

#define stack_pop(stack, data)          do {                \
                                            switch ()\
                                        } while(0);

#endif // STACK_H_