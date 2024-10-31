#ifndef STACK_ERRORS_H_
#define STACK_ERRORS_H_

// PRIVATE HEADER

/**************************************************************************//**
 * @file     errors.h
 * @brief    Stack. C Error codes.
 * @version  V0.0.1
 * @date     24. Sep 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#ifndef __cplusplus

typedef enum {
    STACK_OK                = 0x00,
    STACK_INVALID           = 0x01,

    STACK_ERROR_ALLOCATION  = 0x02,
    STACK_ERROR_FREEING     = 0x03,

    STACK_ERROR_ENCRYPTION  = 0x04,

    STACK_ERROR_PUSH        = 0x05,
    STACK_ERROR_POP         = 0x06,

    STACK_OVERFLOW = STACK_ERROR_ALLOCATION,
    STACK_UNDERFLOW         = 0x07,
} stack_errors_t;


#else
#   error "<stack/errors.h> ERROR: The file can only be included when building in C."
#endif

#endif // STACK_ERRORS_H_