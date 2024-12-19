#pragma clang diagnostic ignored "-Wc99-designator"

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <stdint.h>

typedef enum {

    // -----------------

    INSTR_HLT   = 0x00,
    INSTR_MOV   = 0x01,
    INSTR_CMP   = 0x02,

    INSTR_JMP   = 0x03,
    INSTR_JE    = 0x04,
    INSTR_JL    = 0x05,
    INSTR_JG    = 0x06,

    INSTR_JLE   = 0x07,
    INSTR_JGE   = 0x08,

    INSTR_ADD   = 0x09,
    INSTR_SUB   = 0x0A,
    INSTR_MUL   = 0x0B,
    INSTR_DIV   = 0x0C,
    INSTR_SQRT  = 0x0D,

    INSTR_PUSH  = 0x0E,
    INSTR_POP   = 0x0F,

    INSTR_PRINT = 0x10,

    NUM_INSTRUCTIONS

} opcode_t;

#define PROC_DATA_ADDRESS (1 << 0)
#define PROC_DATA_REGISTER (1 << 1)
#define PROC_DATA_IMMUTABLE (1 << 2)

#define PROC_DATA_READABLE (PROC_DATA_IMMUTABLE | PROC_DATA_REGISTER | PROC_DATA_ADDRESS) 
#define PROC_DATA_WRITABLE (PROC_DATA_REGISTER | PROC_DATA_ADDRESS) 

typedef struct {
    uint8_t imm : 1;
    uint8_t reg : 1;
    uint8_t adr : 1;
    uint64_t value : 61;
} operand_t;

struct { // TODO: ODR violation: you will define this map in every file you include it to, use "inline" or separate it to .cpp
    const char* name;
    int num_of_args;
    int args[3]; // unused
} instructions_map[] = {
    [INSTR_HLT]     = {"hlt", 1, {
            PROC_DATA_READABLE
    }},
    [INSTR_MOV]     = {"mov", 2, { 
        PROC_DATA_WRITABLE,  PROC_DATA_READABLE
    }},
    [INSTR_CMP]     = {"cmp", 2, {
        PROC_DATA_READABLE,  PROC_DATA_READABLE
    }},

    [INSTR_JMP]     = {"jmp", 1, {
        PROC_DATA_IMMUTABLE
    }},
    [INSTR_JE]      = {"je", 1,  {
        PROC_DATA_IMMUTABLE
    }},
    [INSTR_JL]      = {"jl", 1,  {
        PROC_DATA_IMMUTABLE
    }},
    [INSTR_JG]      = {"jg", 1, {
        PROC_DATA_IMMUTABLE
    }},

    [INSTR_JLE]     = {"jle", 1, {
        PROC_DATA_IMMUTABLE
    }},
    [INSTR_JGE]     = {"jge", 1, {
        PROC_DATA_IMMUTABLE
    }},

    [INSTR_ADD]     = {"add", 3, {
        PROC_DATA_WRITABLE, PROC_DATA_READABLE, PROC_DATA_READABLE
    }},
    [INSTR_SUB]     = {"sub", 3, {
        PROC_DATA_WRITABLE, PROC_DATA_READABLE, PROC_DATA_READABLE
    }},
    [INSTR_MUL]     = {"mul", 3, {
        PROC_DATA_WRITABLE, PROC_DATA_READABLE, PROC_DATA_READABLE
    }},
    [INSTR_DIV]     = {"div", 3, {
        PROC_DATA_WRITABLE, PROC_DATA_READABLE, PROC_DATA_READABLE
    }},
    [INSTR_SQRT]    = {"sqrt", 2, {
        PROC_DATA_WRITABLE, PROC_DATA_READABLE, PROC_DATA_READABLE
    }},

    [INSTR_PUSH]    = {"push", 1, {
        PROC_DATA_READABLE
    }},
    [INSTR_POP]     = {"pop", 1, {
        PROC_DATA_READABLE
    }},

    [INSTR_PRINT]   = {"print", 1, {
        -1
    }},
};

typedef struct {
    opcode_t opcode;
    operand_t operands[3];
} instruction_t;


#endif // INSTRUCTIONS_H_
