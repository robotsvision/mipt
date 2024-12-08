#include <cpu_arch.h>

static const char* _instruction_map[_PROCESSOR_OPCODE_NUM] = {
    [PROCESSOR_OPCODE_NOP]      = "nop",
    [PROCESSOR_OPCODE_MOV]      = "mov",
    [PROCESSOR_OPCODE_CMP]      = "cmp",

    [PROCESSOR_OPCODE_JMP]      = "jmp",
    [PROCESSOR_OPCODE_JE]       = "je",
    [PROCESSOR_OPCODE_JL]       = "jl",
    [PROCESSOR_OPCODE_JG]       = "jg",

    [PROCESSOR_OPCODE_JLE]      = "jle",
    [PROCESSOR_OPCODE_JGE]      = "jge",

    [PROCESSOR_OPCODE_ADD]      = "add",
    [PROCESSOR_OPCODE_SUB]      = "sub",
    [PROCESSOR_OPCODE_MUL]      = "mul",
    [PROCESSOR_OPCODE_DIV]      = "div",
    [PROCESSOR_OPCODE_SQRT]     = "sqrt",

    [PROCESSOR_OPCODE_PUSH]     = "push",
    [PROCESSOR_OPCODE_POP]      = "pop",

    [PROCESSOR_OPCODE_PRINT]    = "prt",

    [PROCESSOR_OPCODE_INT]      = "int",
};

struct {
    const char* name;
    size_t num_of_args;
} _instruction_map[] = {
    [PROCESSOR_OPCODE_MOV]      = {"mov", 2},
    [PROCESSOR_OPCODE_CMP]      = {"cmp", 2},
    [PROCESSOR_OPCODE_NOP]      = {"nop", 0},

    [PROCESSOR_OPCODE_JMP]      = {"jmp", 1},
    [PROCESSOR_OPCODE_JE]       = {"je", 1},
    [PROCESSOR_OPCODE_JL]       = {"jl", 1},
    [PROCESSOR_OPCODE_JG]       = {"jg", 1},

    [PROCESSOR_OPCODE_JLE]      = {"jle", 1},
    [PROCESSOR_OPCODE_JGE]      = {"jge", 1},

    [PROCESSOR_OPCODE_ADD]      = {"add", 2},
    [PROCESSOR_OPCODE_SUB]      = {"sub", 2},
    [PROCESSOR_OPCODE_MUL]      = {"mul", 2},
    [PROCESSOR_OPCODE_DIV]      = {"div", 2},
    [PROCESSOR_OPCODE_SQRT]     = {"sqrt", 1},

    [PROCESSOR_OPCODE_PUSH]     = {"push", 1},
    [PROCESSOR_OPCODE_POP]      = {"pop", 1},

    [PROCESSOR_OPCODE_PRINT]    = {"prt", 1},

    [PROCESSOR_OPCODE_INT]      = {"int", 1},
}; 

const char* get_opcode_name(opcode_t opcode) {
    return _instruction_map[(int)opcode];
}