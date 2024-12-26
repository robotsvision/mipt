#include "assembler.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "instructions.h"


void assemble(const char* filename, generated_code_t* output) {
    assert(filename != NULL);
    assert(output != NULL);

    FILE* file_descriptor = fopen(filename, "rb");

    if (!file_descriptor)
        return;

    char buffer[255] = "";
    size_t output_offset = 0;

    output->output = (int64_t*)calloc(1024, sizeof(int64_t));
    output->size = 0;

    while (fscanf(file_descriptor, "%s", buffer) == 1) {
        if (strchr(buffer, ';') != NULL) {
            while (fscanf(file_descriptor, "%s", buffer) == 1) {
                if (strchr(buffer, '\n') != NULL) {
                    break;
                }
            }
            continue;
        }

        instruction_t instruction = {
            .opcode = INSTR_HLT,
            .operands = {0},
        };
        bool found_instruction = false;

        for (size_t i = 0; i < NUM_INSTRUCTIONS; ++i) {
            if (strcmp(buffer, instructions_map[i].name) == 0) {
                instruction.opcode = (opcode_t)i;
                found_instruction = true;
                break;
            }
        }

        if (found_instruction) {
            int num_args = instructions_map[instruction.opcode].num_of_args;
            for (int i = 0; i < num_args; ++i) {
                fscanf(file_descriptor, "%s", buffer);
                operand_t operand = {
                    .imm = 0,
                    .reg = 0,
                    .adr = 0,
                    .value = 0
                };

                if (buffer[0] == 'R') {
                    operand.reg = 1;
                    operand.value = atoll(buffer + 1);
                } else if (buffer[0] == '*') {
                    operand.adr = 1;
                    operand.value = atoll(buffer + 1);
                } else if (isdigit(buffer[0])) {
                    operand.imm = 1;
                    operand.value = atoll(buffer);
                } else {
                    printf("Error! Invalid token: '%s'\n", buffer);
                    fclose(file_descriptor);
                    free(output->output);
                    return;
                }

                instruction.operands[i] = operand;
            }

            if (output_offset + 1 + num_args >= output->size) {
                output->output = (int64_t*)realloc(output->output, (output->size + 1024) * sizeof(int64_t));
                output->size += 1024;
            }

            output->output[output_offset++] = instruction.opcode;
            for (int i = 0; i < num_args; ++i) {
                output->output[output_offset++] = *((int64_t*)&instruction.operands[i]);
            }
        } else {
            printf("Error! Invalid token: '%s'\n", buffer);
            fclose(file_descriptor);
            free(output->output);
            return;
        }
    }

    output->size = output_offset;
    fclose(file_descriptor);
    return;
}