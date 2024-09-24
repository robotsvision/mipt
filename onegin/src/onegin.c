#include <onegin.h>

/*************************************************************
 * Private
 ************************************************************/

// Standard libs
#include <stdlib.h>

// Onegin libs
#include <types/utf8.h>


/*************************************************************
 * Public
 ************************************************************/

int onegin_run(int argc, const char* argv[]) {
    const utf8_string_t string1 = UTF8_CSTR("aab");
    const utf8_string_t string2 = UTF8_CSTR("bbb");

    utf8_string_t mem_block1 = calloc(utf8_len(string1), sizeof(char));
    utf8_string_t mem_block2 = calloc(utf8_len(string2), sizeof(char));

    return EXIT_SUCCESS; // TODO: memory leak?
}
