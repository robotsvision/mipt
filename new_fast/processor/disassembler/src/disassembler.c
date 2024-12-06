#include <disassembler.h>
#include <utils.h>

#include <alloca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


bin_code_t asm_code_generate(const void* src, size_t size) {
    if (UNLIKELY(
        src == NULL || 
        size == 0 || 
        size % sizeof(instruction_t) != 0
        ))
    {
        return (bin_code_t){.content = NULL, .size = 0 };
    }
    return (bin_code_t){ .content = (instruction_t*)(src), .size = size };
}

dasm_error_t dasm_generate(asm_code_t* dest, const bin_code_t src, const size_t src_size) {
    
    if (UNLIKELY(dest == NULL))
        return DASM_ERROR_NO_DEST;
    
    if (UNLIKELY(src.content == NULL || src.size == 0))
        return DASM_ERROR_NO_SRC;

    // \t [opcode] [operand], [operand] (\n or \0)
    const size_t each_line_max_length = 1 + 4 + 10 + 1 + 10 + 1; 
    asm_code_content_t assembler_code = calloc(src_size, each_line_max_length);
    
    if (UNLIKELY(assembler_code == NULL)) {
        return DASM_ERROR_ALLOC;
    }

    char* operand_buffer = alloca(20 * sizeof(char));

    if (UNLIKELY(operand_buffer == NULL)) {
        free(assembler_code);
        return DASM_ERROR_ALLOC;
    }

    asm_code_content_t dest_ptr = assembler_code;
    for (size_t i = 0; i < src_size; ++i) {
        if (is_opcode_valid(src.content[i].opcode)) {

            (*dest_ptr) = '\t';

            const char* opcode_name = get_opcode_name(src.content[i].opcode);
            size_t opcode_name_len = strlen(opcode_name);

            memcpy(dest_ptr, opcode_name, opcode_name_len);

            dest_ptr += opcode_name_len;

            (*dest_ptr) = '\t';

            dest_ptr += 1;

            if (src.content[i].imm1 == true) {
                dest_ptr += sprintf(dest_ptr, "%d", src.content[i].op1);
            } else {
                if ()
            }

            (*dest_ptr) = ' ';

            if (src.content[i].imm2 == true) {
                dest_ptr += sprintf(dest_ptr, "%d", src.content[i].op1);
            } else {
               
            }

            

        } else {
            return DASM_ERROR_OPCODE_INVALID;
        }
    }

    // realloc();
    return DASM_OK;
}

