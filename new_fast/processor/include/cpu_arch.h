#ifndef CPU_ARCH_H_
#define CPU_ARCH_H_

/**************************************************************************//**
 * @file     cpu_arch.h
 * @brief    Instructions enumerations and basic data types for processor.
 * @version  V0.2.0
 * @date     1. Dec 2024
 * @author   Matvey Rybalkin
******************************************************************************/

/*---------------------------------------------------------------------------*/
/*                              The CPU Architecture                         */
/* Hoping for greatness, we've added multi-core support!                     */
/*---------------------------------------------------------------------------*/

/*----------------------------- Registers -----------------------------------*/
/*    Number of Registers: 16 to 128 per core                                */
/*    Address range (per core): 0x00 -> n                                    */
/*    Registers are private to each core.                                    */
/*---------------------------------------------------------------------------*/

/*----------------------------- RAM -----------------------------------------*/
/*    Shared memory accessible by all cores.                                */
/*    Address range: n -> s                                                  */
/*    Synchronization required for concurrent access.                        */
/*---------------------------------------------------------------------------*/

/*----------------------------- Stack ---------------------------------------*/
/*    Private stack for each core, allocated within shared memory.           */
/*    Address range (per core): s -> top                                     */
/*    Each core manages its own stack pointer.                               */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*    ^                                                                      */
/*    |                                                                      */
/*    |                                                                      */
/*    Address growth direction (stack grows downward).                       */
/*---------------------------------------------------------------------------*/

/*----------------------------- Text ----------------------------------------*/
/*    Executable instructions loaded into shared memory.                     */
/*    Each core fetches instructions independently.                          */
/*---------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief System-wide data type for processing operations.
 */
typedef int64_t sys_t;

/**
 * @brief Enumeration of processor opcodes.
 * 
 * Defines the operation codes supported by the processor, 
 * including arithmetic, control flow, and system-level operations.
 */
typedef enum {
    PROCESSOR_OPCODE_NOP    = 0x00, /**< No operation. */
    PROCESSOR_OPCODE_MOV    = 0x01, /**< Move data between registers or memory. */
    PROCESSOR_OPCODE_CMP    = 0x02, /**< Compare two operands. */

    PROCESSOR_OPCODE_JMP    = 0x03, /**< Unconditional jump. */
    PROCESSOR_OPCODE_JE     = 0x04, /**< Jump if equal. */
    PROCESSOR_OPCODE_JL     = 0x05, /**< Jump if less. */
    PROCESSOR_OPCODE_JG     = 0x06, /**< Jump if greater. */

    PROCESSOR_OPCODE_JLE    = 0x07, /**< Jump if less or equal. */
    PROCESSOR_OPCODE_JGE    = 0x08, /**< Jump if greater or equal. */

    PROCESSOR_OPCODE_ADD    = 0x09, /**< Add two operands. */
    PROCESSOR_OPCODE_SUB    = 0x0A, /**< Subtract two operands. */
    PROCESSOR_OPCODE_MUL    = 0x0B, /**< Multiply two operands. */
    PROCESSOR_OPCODE_DIV    = 0x0C, /**< Divide two operands. */
    PROCESSOR_OPCODE_SQRT   = 0x0D, /**< Calculate square root. */

    PROCESSOR_OPCODE_PUSH   = 0x0E, /**< Push value onto the stack. */
    PROCESSOR_OPCODE_POP    = 0x0F, /**< Pop value from the stack. */

    PROCESSOR_OPCODE_PRT    = 0x10, /**< Print a value to the output. */

    PROCESSOR_OPCODE_INT    = 0x11, /**< Trigger an interrupt. */

    _PROCESSOR_OPCODE_NUM   /**< Total number of opcodes. */
} opcode_t;


/**
 * @brief Checks if the given opcode is valid.
 * 
 * For verifying whether the specified opcode corresponds to a valid processor instruction.
 * Useful for ensuring that an opcode can be safely processed or executed.
 * 
 * @param opcode The opcode to validate.
 * @return `true` if the opcode is valid, `false` otherwise.
 * 
 * @note A valid opcode is one that falls within the range of defined processor opcodes.
 */
extern bool is_opcode_valid(opcode_t opcode);

/**
 * @brief Retrieves the name of the instruction for a given opcode.
 * 
 * For obtaining a human-readable string representation of a processor instruction
 * based on its opcode. Useful for debugging, logging, or disassembling binary code.
 * 
 * @param opcode The opcode of the instruction to retrieve the name for.
 * @return A pointer to a null-terminated string containing the instruction name.
 * 
 * @note Ensure the opcode is valid using `is_opcode_valid()` to avoid unexpected results.
 */
extern const char* get_opcode_name(opcode_t opcode);

/**
 * @brief Enumeration of processor interrupts.
 * 
 * Represents interrupt identifiers for system-level events.
 */
typedef enum {
    INTERRUPT_ /**< Placeholder for interrupt enumeration. */
} interrupt_t;

/**
 * @brief Packed structure for a single processor instruction.
 * 
 * Encapsulates the opcode, operands, and flags for a single instruction.
 */
typedef struct {
    opcode_t    opcode  : 8;  /**< Operation code for the instruction. */
    uint32_t    op1     : 10; /**< First operand (10 bits). */
    uint32_t    op2     : 10; /**< Second operand (10 bits). */
    uint32_t    imm1    : 1;  /**< Immutable flag for first operand */
    uint32_t    imm2    : 1;  /**< Immutable flag for second operand */
    uint32_t    flags   : 2;  /**< Flags for the instruction. */
} __attribute__((packed)) instruction_t;

/**
 * @brief Binary code content type.
 * 
 * A pointer to an array of packed `instruction_t` structures.
 */
typedef instruction_t* bin_code_content_t;

/**
 * @brief Assembly code content type.
 * 
 * A pointer to a null-terminated string representing assembly code.
 */
typedef char* asm_code_content_t;

/**
 * @brief Structure for binary code representation.
 * 
 * Encapsulates the size and content of binary-encoded instructions.
 */
typedef struct {
    const size_t size;           /**< Size of the binary code in bytes. */
    bin_code_content_t content;  /**< Pointer to the binary code content. */
} bin_code_t;

/**
 * @brief Structure for assembly code representation.
 * Encapsulates the size and content of assembly code as a string.
 */
typedef struct {
    const size_t size;           /**< Size of the assembly code in bytes. */
    asm_code_content_t content;  /**< Pointer to the assembly code content. */
} asm_code_t;

#define REGISTER_AREA_SIZE(num_of_regs) (const size_t)(sizeof(sys_t) * num_of_regs)

/**
 * @brief CPU configuration structure.
 * 
 * This structure defines the configuration of the virtual CPU, including the
 * number of registers and the size of RAM.
 */
typedef struct {
    /**
     * @brief Number of registers.
     * 
     * Specifies the total number of general-purpose registers available in
     * the CPU. This value must be in the range 16  to 128.
     */
    const size_t R_size;

    /**
     * @brief Size of RAM in bytes.
     * 
     * Specifies the total size of the RAM available to the CPU. This memory
     * is used for storing program data and dynamic allocations.
     */
    const size_t RAM_size;
} cpu_conf_t;

typedef struct {
    sys_t ic;
    sys_t flags;
    size_t R_size;
    sys_t* R;
} core_t;

typedef struct {
    sys_t* RAM;

} shared_memory_t;

typedef struct {
    core_t* cores;
    
} cpu_t;

/**
 * @brief Null pointer representation for processor-specific definitions.
 */
#define PROCESSOR_NULL_PTR 0U

#endif // CPU_ARCH_H_
