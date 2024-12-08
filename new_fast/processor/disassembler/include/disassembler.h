#ifndef DISASSEMBLER_H_
#define DISASSEMBLER_H_

/**************************************************************************//**
 * @file     disassembler.h
 * @brief    Functions for disassembling .bin file to assembler text.
 * @version  V0.2.0
 * @date     2. Dec 2024
 * @author   Matvey Rybalkin
******************************************************************************/

#include <cpu_arch.h>
#include <stdlib.h>

/**
 * @brief Error codes for disassembly operations.
 * 
 * Use these codes to determine the result of disassembly-related functions.
 */
typedef enum {
    /**
     * @brief Operation completed successfully.
     */
    DASM_OK,

    /**
     * @brief Destination pointer is `NULL`.
     * 
     * Indicates that the destination structure required for the operation
     * was not provided or is invalid.
     */
    DASM_ERROR_NO_DEST,

    /**
     * @brief Source data is invalid or `NULL`.
     * 
     * Indicates that the binary source data required for the operation
     * was not provided or is invalid.
     */
    DASM_ERROR_NO_SRC,

    /**
     * @brief Memory allocation failed.
     * 
     * Indicates that the required memory could not be allocated during the operation.
     * This error typically occurs when the system runs out of memory or the requested 
     * allocation size is invalid.
     */
    DASM_ERROR_ALLOC,

    /**
     * @brief Invalid opcode encountered.
     * 
     * Indicates that the provided opcode does not correspond to any valid processor instruction.
     * This error typically occurs when decoding or validating binary data that contains unknown 
     * or unsupported opcodes.
     * 
     * @note Ensure the opcode is validated using `is_opcode_valid()` before performing operations
     * that depend on it.
     */
    DASM_ERROR_OPCODE_INVALID,


} dasm_error_t;


/**
 * @brief Creates a new `bin_code_t` structure from raw binary data.
 * 
 * For encapsulating raw binary data into a `bin_code_t` structure,
 * use this function to initialize the structure with the given data and size.
 * 
 * @param src Pointer to the source buffer containing raw binary data. Must not be `NULL`.
 * @param size Size of the source buffer in bytes. Must be greater than 0.
 * @return A `bin_code_t` structure initialized with the provided data. 
 * If the input is invalid (`src == NULL` or `size == 0`), returns a structure with `.size = 0`.
 */
extern bin_code_t bin_code_duplicate(const void* src, size_t size);

extern dasm_error_t dasm_generate(asm_code_t* dest, const bin_code_t src, cpu_t* processor);

#endif // DISASSEMBLER_H_