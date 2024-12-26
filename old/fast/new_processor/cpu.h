#ifndef CPU_H_
#define CPU_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "instructions.h"

#define CPU_CONF_REGISTERS_N 32

typedef int64_t sys_t;

typedef struct {
    sys_t R[CPU_CONF_REGISTERS_N];
    size_t ic;
    sys_t* RAM;
} cpu_t;

typedef enum {

} cpu_error_t;

cpu_t cpu_create(size_t ram_size, cpu_error_t* error);
cpu_error_t cpu_validate(cpu_t* CPU);
cpu_error_t cpu_run(cpu_t* CPU, instruction_t instrns[], size_t num_of_instrns);
void cpu_print_status()
void cpu_destroy(cpu_t* cpu);




#endif // CPU_H_