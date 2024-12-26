#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int64_t* output;
    size_t size;
} generated_code_t;

extern void assemble(const char* file, generated_code_t* output);

#endif // ASSEMBLER_H_