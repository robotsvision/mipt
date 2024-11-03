#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Систесный тип
typedef int64_t sys_t;
typedef uint64_t usys_t;

// Регистры
struct {
    sys_t r[16];
    usys_t pc;
} registers;

// ОЗУ
#define MEMORY_SIZE 8192UL
sys_t RAM[MEMORY_SIZE];

typedef void (*instruction_func_t)(sys_t* operands[]);

typedef struct {
    const char* name;
    instruction_func_t function;
    size_t num_of_operands;
} instruction_entry_t;

void instr_stop(sys_t* operands[]) {
    printf("Стоп!\n");
    exit(0);
}

void instr_add(sys_t* operands[]) {
    *operands[0] = *operands[1] + *operands[2];
}

void instr_sub(sys_t* operands[]) {
    *operands[0] = *operands[1] - *operands[2];
}

void instr_mul(sys_t* operands[]) {
    *operands[0] = *operands[1] * *operands[2];
}

void instr_div(sys_t* operands[]) {
    if (*operands[2] == 0) {
        printf("Деление на ноль!\n");
        instr_stop(NULL);
    } else {
        *operands[0] = *operands[1] / *operands[2];
    }
}

void instr_jmp(sys_t* operands[]) {
    registers.pc = *operands[0];
}

void instr_bqe(sys_t* operands[]) {
    if (*operands[0] == *operands[1]) {
        registers.pc = *operands[2];
    }
}

void instr_bne(sys_t* operands[]) {
    if (*operands[0] != *operands[1]) {
        registers.pc = *operands[2];
    }
}

instruction_entry_t instructions[] = {
    { "stop", instr_stop, 0 },
    { "add", instr_add, 3 },
    { "sub", instr_sub, 3 },
    { "mul", instr_mul, 3 },
    { "div", instr_div, 3 },
    { "jmp", instr_jmp, 1 },
    { "bqe", instr_bqe, 3 },
    { "bne", instr_bne, 3 }
};
#define NUM_INSTRUCTIONS (sizeof(instructions) / sizeof(instruction_entry_t))

instruction_entry_t* find_instruction(const char* name) {
    for (size_t i = 0; i < NUM_INSTRUCTIONS; ++i) {
        if (strcmp(instructions[i].name, name) == 0) {
            return &instructions[i];
        }
    }
    return NULL;
}

void execute_instruction(const char* name, sys_t* operands[]) {
    instruction_entry_t* instr = find_instruction(name);
    if (instr != NULL) {
        // исправлю (если будут другие без операторов)
        if (instr->num_of_operands != 0) {
            instr->function(operands);
        } else {
            instr->function(NULL); // только stop без операндов
        }
    } else {
        printf("Не знаю такой инструкции: %s\n", name);
    }
}

int main(void) {
    registers.r[0] = 10;
    registers.r[1] = 20;
    registers.r[2] = 0;  // Для результата

    sys_t* operands_add[] = { &registers.r[2], &registers.r[0], &registers.r[1] };
    execute_instruction("add", operands_add);
    printf("R2 (10 + 20): %lld\n", registers.r[2]);  // 30

    sys_t* operands_sub[] = { &registers.r[2], &registers.r[2], &registers.r[0] };
    execute_instruction("sub", operands_sub);
    printf("R2 (30 - 10): %lld\n", registers.r[2]);  // 20

    sys_t* operands_mul[] = { &registers.r[2], &registers.r[2], &registers.r[1] };
    execute_instruction("mul", operands_mul);
    printf("R2 (20 * 20): %lld\n", registers.r[2]);  // 400

    sys_t* operands_div[] = { &registers.r[2], &registers.r[2], &registers.r[0] };
    execute_instruction("div", operands_div);
    printf("R2 (400 / 10): %lld\n", registers.r[2]);  // 40

    execute_instruction("stop", NULL);
    return 0;
}
