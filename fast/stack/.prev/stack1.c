// TODO: delete this

/**
 * Быстрый Стек
 * 
 * 
 * 
 */

#ifndef _linux_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define __USE_GNU
#include <sys/mman.h>
////////////////////////////////////////
////// Определение конфигурации ////////
////////////////////////////////////////

#define STACK_INITIAL_SIZE 4096UL

////////////////////////////////////////
////////// Определение типов ///////////
////////////////////////////////////////


/******************************************************************/
// ---------------------------- STACK ----------------------------
/******************************************************************/

typedef struct {
    void* data;
    size_t sizeof_element;
    size_t capacity;
    size_t used;
} stack_t;

typedef enum {
    TYPE_PTR,
    TYPE_CHAR,
    TYPE_UINT8,
    TYPE_UINT16,
    TYPE_UINT32,
    TYPE_UINT64,
    TYPE_INT8,
    TYPE_INT16,
    TYPE_INT32,
    TYPE_INT64,
    TYPE_FLOAT32,
    TYPE_FLOAT64,
    TYPE_LONGFLOAT,
} type_t;

static const size_t _get_type_size[] = {
    [TYPE_PTR]          = sizeof(void*),
    [TYPE_CHAR]         = sizeof(char),
    [TYPE_UINT8]        = sizeof(uint8_t),
    [TYPE_UINT16]       = sizeof(uint16_t),
    [TYPE_UINT32]       = sizeof(uint32_t),
    [TYPE_UINT64]       = sizeof(uint64_t),
    [TYPE_INT8]         = sizeof(int8_t),
    [TYPE_INT16]        = sizeof(int16_t),
    [TYPE_INT32]        = sizeof(int32_t),
    [TYPE_INT64]        = sizeof(int64_t),
    [TYPE_FLOAT32]      = sizeof(float),
    [TYPE_FLOAT64]      = sizeof(double),
    [TYPE_LONGFLOAT]    = sizeof(long double),
};

typedef union {
    void* ptr;
    char character;
    uint8_t  uint8;
    uint16_t uint16;
    uint32_t uint32;
    uint64_t uint64;
    int8_t  int8;
    int16_t int16;
    int32_t int32;
    int64_t int64;
    float float32;
    double float64;
    long double long_double;
} any_t;

#define STACK_INCREASE_COEFF (double)(2.0)
#define STACK_DECREASE_COEFF (double)(0.25)
#define STACK_DIVIDER 2

typedef enum {
    STACK_ERROR_UNINITIALIZED,
    STACK_ERROR_NO_DATA,
    STACK_ERROR_DATA_CORRUPTED
} stack_error_t;


int stack_expand(stack_t* stack) {
    if (stack->capacity <= stack->used + sizeof(long double)) {
        stack->data = mremap
        (
            stack->data,
            stack->capacity,
            stack->capacity * STACK_INCREASE_COEFF,
            MREMAP_MAYMOVE
        );
        if (stack->data == MAP_FAILED) {
            return -1;
        }
    }
}


int stack_strip(stack_t* stack) {
    if (stack->used < (size_t)(STACK_DECREASE_COEFF * stack->capacity)) {
        stack->data = mremap
        (
            stack->data,
            stack->capacity,
            stack->capacity / STACK_DIVIDER,
            MREMAP_MAYMOVE
        );
        if (stack->data == MAP_FAILED) {
            return -1;
        }
    }
    return 0;
}

int stack_init(stack_t* stack, size_t sizeof_element) {
    (*stack) = (stack_t){
        .capacity = STACK_INITIAL_SIZE * sizeof_element,
        .used = 0UL,
        .sizeof_element = sizeof_element,
        .data 
        = mmap(
            NULL, 
            STACK_INITIAL_SIZE * sizeof_element, 
            PROT_READ | PROT_WRITE, 
            MAP_ANONYMOUS, 
            -1, 
            0
        ),
    };
    if (stack->data == MAP_FAILED) {
        return NULL;
    }
    return stack;
}

int stack_push(stack_t* stack, any_t data, type_t type) {
    if (stack == NULL || stack->data == MAP_FAILED) {
        return -1;
    }

    switch (_get_type_size[type]) {
        case 1UL: 
            *(uint8_t*)(stack->data + stack->used) = data.uint8;
            stack->used += 1;
            break;
        case 2UL:
            *(uint16_t*)(stack->data + stack->used) = data.uint16;
            stack->used += 2;
            break;
        case 4UL:
            *(uint32_t*)(stack->data + stack->used) = data.uint32;
            stack->used += 4;
            break;
        case 8UL:
            *(uint64_t*)(stack->data + stack->used) = data.uint64;
            stack->used += 8;
            break;
        case sizeof(long double):
            *(long double*)(stack->data + stack->used) = data.long_double;
            stack->used += sizeof(long double);
            break;
    }

    stack_expand(stack);

    return 0;
}

type_t stack_pop_type() {

}

any_t stack_pop_value() {

}


/******************************************************************/
// -------------------- ПРИМЕР ИСПОЛЬЗОВАНИЯ ----------------------
/******************************************************************/

int main() {
    const int x = 10;
    const int y = 20;
    const int *p1 = &x;
    const int * const * const ptr = &p1;
}


#else
#   error "Приложение сделано только для Линукс"
#endif
