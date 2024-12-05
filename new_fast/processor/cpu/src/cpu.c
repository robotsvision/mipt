#include <cpu.h>
#include <string.h>

// -----------------------------------------------------------
// ------------------------------------- PRIVATE FUNCTIONS
// -----------------------------------------------------------


static inline int _deref_cpu_address(sys_t* value, cpu_t cpu, sys_t ptr) {
    if (ptr == PROCESSOR_NULL_PTR)
        return -1;

    sys_t* data_ptr = NULL;

    if (ptr < cpu.conf.R_size) {
        data_ptr = cpu.R + ptr;
    } else {
        data_ptr = cpu.RAM + ptr - cpu.conf.R_size;
    }

    (*value) = (*data_ptr);
    return 0;
}

static void _execute_instruction(instruction_t instr) {
    switch (instr.opcode) {
        case PROCESSOR_OPCODE_ADD: {

        }
            break;

        case PROCESSOR_OPCODE_NOP:
            break;

    }
}

static void _cpu_reset_regs(cpu_t* cpu) {
    cpu->ic = 0;
    cpu->flags = 0;
    memset(cpu->R, 0, PROCESSOR_REGS_NUM * sizeof(sys_t));
}

static void _cpu_reset_ram(cpu_t* cpu){
    if (cpu->RAM == NULL && cpu->RAM_size == 0UL)
        return;

    memset(cpu->RAM, 0, cpu->RAM_size);
}


// -----------------------------------------------------------
// ------------------------------------- PUBLIC FUNCTIONS 
// -----------------------------------------------------------


cpu_t* cpu_create(const size_t ram_size) {

    if (ram_size == 0UL)
        return INVALID_CPU;

    cpu_t* processor = calloc(1, sizeof(cpu_t*));
    processor->RAM = calloc(ram_size, sizeof(sys_t));

    if (processor->RAM == NULL) {
        return INVALID_CPU;
    }
        
    _cpu_reset_regs(processor);

    processor->R_size = 

    return processor;
}

void cpu_execute(cpu_t* restrict cpu, const bin_code_t code, const size_t bin_code_size) {
    
    if (bin_code_size % sizeof(instruction_t) != 0)
        return;

    const size_t num_of_instructions = bin_code_size / sizeof(instruction_t);

    _execute_instruction();
}

const char* cpu_dump(cpu_t* cpu) {
    return NULL;
}

void cpu_destroy(cpu_t* cpu) {


}
