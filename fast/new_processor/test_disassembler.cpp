#include "utest.h"
#include "disassembler.h"

instruction_t examples[][3] = {

    {
        (instruction_t){
            .opcode = INSTR_ADD, 
            .operands = {
                (operand_t){
                    .adr = false,
                    .imm = false,
                    .reg = true,
                    .value = 0
                },
                (operand_t){
                    .adr = false,
                    .imm = false,
                    .reg = true,
                    .value = 2
                },
                (operand_t){
                    .adr = false,
                    .imm = true,
                    .reg = false,
                    .value = 3
                },
            }
        },
    },

    {
        (instruction_t){
            .opcode = INSTR_PRINT, 
            .operands = {
                (operand_t){
                    .adr = false,
                    .imm = true,
                    .reg = false,
                    .value = 969696
                },
            }
        },
    },
};

const char* answers[] = {
    "0\tadd R0 R2 3",
    "0\tprint 969696",
};

#define NUM_OF_EXAMPLES (sizeof(examples) / sizeof(examples[0]))

int main(void) {
    for (size_t i = 0; i < NUM_OF_EXAMPLES; ++i) {
        printf("\nExample %lu ----> \n", i + 1);
        printf("Real: "); disassemble(examples[i], 1);
        printf("\nExpected: %s", answers[i]);
    }
    return 0;
}
