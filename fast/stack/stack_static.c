#ifndef _linux_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define __USE_GNU
#include <sys/mman.h>

#define STACK_INITIAL_SIZE 4096UL

typedef int32_t stack_element_t;

#define STACK_NO_DATA MAP_FAILED // кринж

typedef struct {
    stack_element_t* data;
    size_t capacity;
    size_t used;
} stack_t;

int stack_init(stack_t* stack) {
    if (stack == NULL)
        return -1;

    (*stack) = (stack_t){
        .capacity = STACK_INITIAL_SIZE * sizeof(stack_element_t),
        .used = 0UL,
        .data 
        = mmap(
            NULL, 
            STACK_INITIAL_SIZE * sizeof(stack_element_t), 
            PROT_READ | PROT_WRITE, 
            MAP_PRIVATE| MAP_ANONYMOUS, 
            -1, 
            0
        ),
    };
    if (stack->data == STACK_NO_DATA)
        return -1;
    return 0;
}

int stack_deinit(stack_t* stack) {
    if (stack == NULL || munmap (stack->data, stack->capacity) != 0)
        return -1;
    (*stack) = (stack_t) {
        .data = STACK_NO_DATA,
        .capacity = 0UL,
        .used = 0UL,
    };
    return 0;
}

int stack_strip(stack_t* stack) {
    if (stack == NULL || stack->data == STACK_NO_DATA)
        return -1;
    if (stack->used < (size_t)(0.25 * stack->capacity)) {
        size_t new_capacity = (size_t)(stack->capacity / 2);
        stack_element_t* new_memory = mremap
        (
            stack->data,
            stack->capacity,
            new_capacity,
            MREMAP_MAYMOVE
        );

        if (new_memory == STACK_NO_DATA)
            return -1;
        
        (*stack) = (stack_t){
            .data = new_memory,
            .capacity = new_capacity
            // used не изменяется
        };
    }
}

int stack_expand(stack_t* stack) {
    if (stack == NULL || stack->data == STACK_NO_DATA)
        return -1;

    if (stack->used + sizeof(stack_element_t) >= (size_t)(stack->capacity)) {
        size_t new_capacity = stack->capacity * 2;
        stack_element_t* new_memory = mremap
        (
            stack->data,
            stack->capacity,
            new_capacity,
            MREMAP_MAYMOVE
        );

        if (new_memory == STACK_NO_DATA)
            return -1;

        (*stack) = (stack_t){
            .data = new_memory,
            .capacity = new_capacity
            // used не изменяется
        };
    }
    return 0;
}

int stack_push(stack_t* stack, stack_element_t element) {
    stack->data[stack->used++] = element;
    stack_expand(stack);
}

int stack_pop(stack_t* stack, stack_element_t* dest) {
    if (stack == NULL || stack->data == STACK_NO_DATA)
        return -1;
    if (stack->capacity == 0)
        return 1;

    (*dest) = stack->data[--stack->used];
    stack_strip(stack);
    return 0;
}

#define STACK_DUMP_TEXT_BUFFER_SIZE 4096UL  // На небольшой стек точно хватит

char* stack_dump(stack_t stack) {
    char buffer[STACK_DUMP_TEXT_BUFFER_SIZE];

    
}

int main(void) {

    stack_t stack;
    stack_t* const stack_ptr = &stack;

    if (stack_init(stack_ptr) < 0){ 
        perror("");
    }

    stack_push(stack_ptr, 10);

    stack_element_t element = 0;
    stack_pop(stack_ptr, &element);
    stack_deinit(stack_ptr);
    return 0;
}

#else
#   error "Приложение сделано только для Линукс"
#endif