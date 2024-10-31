#ifndef STACK_ENCRYPTION_H_
#define STACK_ENCRYPTION_H_

// PRIVATE HEADER

/**************************************************************************//**
 * @file     encryption.h
 * @brief    Stack. C/C++ version. Encryption functions.
 * @version  V0.0.1
 * @date     10. Oct 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#include <stdlib.h>
#include <stdint.h>

uint64_t encode(size_t adr);
size_t decode(uint64_t code);


#endif // STACK_ENCRYPTION_H_