#ifndef CPU_H_
#define CPU_H_

/**************************************************************************//**
 * @file     cpu.h
 * @brief    Processor functions and execution.
 * @version  V0.2.0
 * @date     2. Dec 2024
 * @author   Matvey Rybalkin
******************************************************************************/

/*--------------------------*/ 
/*  -- The greatest CPU --  */
/*--------------------------*/
/*     Registers 16-128     */ // 0x00 -> n
/*--------------------------*/
/*                          */
/*           RAM            */ // n -> s
/*                          */
/*--------------------------*/
/*          Stack           */ // s -> top
/*--------------------------*/
//  |
//  |
//  |
//  |
//  |
/*--------------------------*/
/*           Text           */
/*--------------------------*/

#include <instructions.h>

typedef struct {
    const size_t R_size;
    const size_t RAM_size;
} cpu_conf_t;

typedef struct {
    sys_t ic;
    sys_t flags;
    cpu_conf_t conf;
    sys_t* R;
    sys_t* RAM;
} cpu_t;

#define INVALID_CPU NULL

extern cpu_t* cpu_create(const cpu_conf_t configuration);
extern void cpu_execute(cpu_t* restrict cpu, bin_code_t code);
extern const char* cpu_dump(cpu_t* restrict cpu);
extern void cpu_destroy(cpu_t* restrict cpu);

#endif // CPU_H_