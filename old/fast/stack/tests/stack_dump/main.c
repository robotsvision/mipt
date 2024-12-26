#include <stdlib.h>
#include <stack.h>


int main(void) {

    stack_conf_t conf;

    conf.protection.hash = STACK_NO_HASH;
    conf.protection.use_assert = true;
    conf.protection.use_canary = true;
    conf.protection.use_hardware_protect = true;
    conf.size_of_element = sizeof(long double);

    stack_t* my_stack = stack_create(conf, STACK_DEFAULT_ALLOCATION);

    if (my_stack == NULL) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}