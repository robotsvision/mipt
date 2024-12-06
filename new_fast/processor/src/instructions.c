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

    [PROCESSOR_OPCODE_PRINT]    = "print",

    [PROCESSOR_OPCODE_INT]      = "int",
};

const char* get_opcode_name(opcode_t opcode) {
    return _instruction_map[(int)opcode];
}