
// ЧТО ТО НЕДОПИСАННОЕ..... 

#ifndef _linux_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define __USE_GNU
#include <sys/mman.h>

#include "stack.h"

typedef int64_t sys_t;

// Регистры
struct {
    sys_t rax, rbx, rcx, rdx;
    sys_t rsi, rdi, rsp, rbp;
    sys_t r8, r9, r10, r11, r12, r13, r14, r15;
    sys_t rip;
    uint64_t rflags;
} registers;

// ОЗУ
#define MEMORY_SIZE 8192UL
sys_t RAM[MEMORY_SIZE];


// АЛУ

typedef enum {
    OPERAND_REGISTER,
    OPERAND_IMMEDIATE,
    OPERAND_MEMORY
} operand_type_t;

typedef union {
    operand_type_t type;
    union {
        sys_t* reg;
        sys_t imm;
        sys_t* mem;
    } value;
} operand_t;


typedef int (*instr_func_t)(operand_t, operand_t);

struct {
    const char* name;
    operand_type_t operands;
    instr_func_t function;
} instructions[] = {

    { "add", 2, instr_add },
    { "sub", 2, instr_sub },
    { "mul", 2, instr_mul },
    { "div", 2, instr_div },
};


int main(void) {

    const char* code = 

        "push 10\n"
        "push 100\n"
        "add\n"

        "push 10\n"
        "push 100\n"
        "hlt\n";


}

#else
#   error "Приложение сделано только для Линукс"
#endif