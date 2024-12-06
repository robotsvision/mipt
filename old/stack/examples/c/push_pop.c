#include <stack.h>

int main(int argc, const char* argv[]) {
    
    stack_t st = stack_init();

    printf("You can easily add a new element to the stack,\ntry entering any number:");
    
    int number;
    scanf("%d", &number);
    
    STACK_PUSH(&st, number, 
        STACK_TYPE_INT
        | STACK_TYPE_VALUE
        | STACK_TYPE_SIGNED
    );

    return EXIT_SUCCESS;
}