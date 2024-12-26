#ifndef DISASEMBLER_H_
#define DISASEMBLER_H_

#include "instructions.h"

#include <stdlib.h>
#include <stdint.h>

extern int disasemble_print(const char* filename);
extern void disassemble(instruction_t* instrns, size_t n);

#endif // DISASEMBLER_H_
