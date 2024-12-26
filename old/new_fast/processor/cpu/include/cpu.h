#ifndef CPU_H_
#define CPU_H_

/**************************************************************************//**
 * @file     cpu.h
 * @brief    Processor functions and execution.
 * @version  V0.2.0
 * @date     2. Dec 2024
 * @author   Matvey Rybalkin
******************************************************************************/

#include <cpu_arch.h>

extern cpu_t* cpu_create(const cpu_conf_t configuration);
extern void cpu_execute(cpu_t* restrict cpu, bin_code_t code);
extern const char* cpu_dump(cpu_t* restrict cpu);
extern void cpu_destroy(cpu_t* restrict cpu);

#endif // CPU_H_