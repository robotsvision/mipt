#include "assembler.h"
#include <assert.h>
#include <stdio.h>

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

int main(void) {
    generated_code_t assembler = (generated_code_t){
        .output = NULL,
        .size = 0UL,
    };
    assemble("asm_example.asm", &assembler);
    write_generated_code_to_file("OUTPUT.bin", &assembler);
    return 0;
}