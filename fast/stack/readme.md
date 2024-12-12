# Реализация стека на языке Си

## Пример кода

``` c
#include <stdio.h>
#include <stdbool.h>
#include <stack.h>

int main(void) {

    stack_t* stack = stack_create(NULL, sizeof(int));

    if (stack == NULL)
        return EXIT_FAILURE;

    for (int i = 0; i < 20; ++i) {      // 20 !!!
        stack_push_4bytes(&stack, i);
    }

    stack_set_acess(&stack, STACK_NO_ACESS);

    char* const dump = stack_dump(&stack);


    // do something

    stack_set_acess(&stack, STACK_READ_WRITE);

    for (int i = 0; i < 19; ++i) {      // 19 !!!
        int buffer = stack_pop_4bytes(&stack);
        printf("[%d]: pop stack: %d\n", i, buffer);
    }

    printf("The last element is: %d\n", );

    printf("Stack is %sempty.\n", stack_is_empty(&stack) == true ? "" : "not ");

    printf("The last element is: %d\n", stack_pop_4bytes(&stack));

    printf("Stack is %sempty.\n", stack_is_empty(&stack) == true ? "" : "not ");

    stack_destroy(&stack);
    return EXIT_SUCCESS;
}
```


## Функции

``` c

// General

extern stack_t* stack_create(stack_conf_t configuration);
extern void stack_destroy(stack_t* stack);

extern void stack_push(stack_t* stack, void* element);
extern void stack_pop(stack_t* stack, void* element);
extern void stack_peek(stack_t* stack, void* element);

extern size_t stack_get_size(stack_t* stack);
extern size_t stack_get_capacity(stack_t* stack);

extern bool stack_is_empty(stack_t* stack);

char* stack_dump(stack_t* stack);
char* stack_dump_html(stack_t* stack);
char* stack_dump_markdown(stack_t* stack);

// Private functions

bool _stack_try_shrink(stack_t* stack);
bool _stack_try_extend(stack_t* stack);

bool _stack_lock(stack_t* stack);
bool _stack_unlock(stack_t* stack);

bool _stack_check_canary(stack_t* stack);
bool _stack_check_hash(stack_t* stack);
bool _stack_check_struct(stack_t* stack);

```
