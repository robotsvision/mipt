#include "disassembler.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "instructions.h"

//#define IN_OPCODE_RANGE(opcode) ((opcode > 0 && opcode < INSTR_POP) || (opcode >= INSTR_HLT && opcode <= INSTR_PRINT))

uint8_t _get_value_type(uint64_t operand) {
    return (uint8_t)(~(UINT64_MAX >> 8) & operand) >> ((sizeof(operand) - 1) * 8);
}

/*

void disassemble(const char* buffer, size_t buffer_size) {
    // prints to stdout disassembly of buffer

    for (int i = 0; i < buffer_size;) {
        assert(buffer[i] <= NUM_INSTRUCTIONS);
        
        printf("0x%06x \t %s: ", i, instructions_map[(int)(buffer[i])].name);
        
        const int instruction = buffer[i];
        const int expected_num_of_args = instructions_map[(int)(buffer[i])].num_of_args;
        const int* expected_arg_types = instructions_map[(int)(buffer[i])].args;
        i += sizeof(uint64_t);

        printf("Arg types: \n");
        for (int j = 0; j < expected_num_of_args; ++j) {

            uint64_t arg_value = *(uint64_t*)(buffer + i);
            uint64_t arg_type = _get_value_type(arg_value);

            printf("ADDRESS     = %d\n", (bool)(arg_type & PROC_DATA_ADDRESS));
            printf("IMMUTABLE   = %d\n", (bool)(arg_type & PROC_DATA_IMMUTABLE));
            printf("REGISTER    = %d\n", (bool)(arg_type & PROC_DATA_REGISTER));


        }
        i += expected_num_of_args * 8;
        printf("\n\n");
    }
}

*/

void disassemble(instruction_t* instrns, size_t n) {
    assert(instrns != NULL);
    for (size_t i = 0; i < n; ++i) {
        printf("%5zu \t", i);
        printf("%s ", instructions_map[instrns[i].opcode].name);

        size_t num_args = instructions_map[instrns[i].opcode].num_of_args;
        for (size_t j = 0; j < num_args; ++j) {
            if (instrns[i].operands[j].adr) {
                putc('*', stdout);
            }

            if (instrns[i].operands[j].reg) {
                putc('R', stdout);
            }
            printf("%lu", instrns[i].operands[j].value);
            if (j + 1 != num_args)
                putc(' ', stdout);
        }
        if (i + 1 != n)
            printf("\n");
    }
}

int disasemble_print(const char* filename) {

    int file_descriptor = open(filename, O_RDONLY);

    if (file_descriptor < 0)
        return -1;

    struct stat file_info;
    stat(filename, &file_info);
    const size_t file_size = file_info.st_size;

    char* file_buffer = (char*)calloc(file_size + 1, sizeof(char));
    
    if (file_buffer == NULL) {
        close(file_descriptor);
        return -1;
    }

    read(file_descriptor, file_buffer, file_size);
    // file_buffer[file_size] = '\0'; // ?

    // disassemble(file_buffer, file_size);

    return 0;
}
