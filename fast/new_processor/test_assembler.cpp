#include "assembler.h"
#include <assert.h>
#include <stdio.h>
#include "disassembler.h"

void write_generated_code_to_file(const char* filename, const generated_code_t* output) {
    assert(filename != NULL);
    assert(output != NULL);

    FILE* file_descriptor = fopen(filename, "wb");
    if (!file_descriptor) {
        printf("Error! Unable to open file: '%s'\n", filename);
        return;
    }

    fwrite(output->output, sizeof(int64_t), output->size, file_descriptor);
    fclose(file_descriptor);
}

int main(int argc, const char *argv[]) {
    generated_code_t assembler = (generated_code_t){
        .output = NULL,
        .size = 0UL,
    };
    assemble(argv[1], &assembler);
    write_generated_code_to_file("OUTPUT.bin", &assembler);

    // TODO: at least test it:
    disassemble((instruction_t*)assembler.output, assembler.size);

    // TODO: none of your .asm example are working, most of them don't even assemble without an error.
    return 0;
}
