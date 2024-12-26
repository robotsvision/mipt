#include <akinator.h>
#include <bintree.h>
#include <resources.h>

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* ============= Private functions ============= */

typedef long file_len_t;
static file_len_t _get_file_size(FILE *file) {
    if (!file) return -1;
    fseek(file, 0, SEEK_END);
    file_len_t size = ftell(file);
    rewind(file);
    return size;
}


/* ============= Global functions ============= */

void akinator_print_message(akinator_res_t msg) {
    if (msg < _AKINATOR_NUM_RES){
        puts(akinator_get_res(msg));
    }
}

tree_t* akinator_load_external(const char* filename) {
    
    FILE* data_file = fopen(filename, "rb");
    if (!data_file)
        return NULL;

    file_len_t len =  _get_file_size(data_file);
    if (len == -1) {
        goto _load_ext_end;
    }

    tree_t* generated_tree = calloc(1, sizeof(tree_t));
    char* file_content = calloc(len, sizeof(char));

    if (!generated_tree || !file_content)
        goto _load_ext_end;


    bool tree_expired = false;
    uint32_t tree_depth = 0U;
    while (!tree_expired) {
        char* next_line = strchr(file_content, '\n');
        char* next_indent = strchr(file_content, '\t');

    }

    /* ============= Freeing data ============= */
_load_ext_end:

    return generated_tree;
}

void akinator_unload_external(const char* filename, tree_t* restrict data_base) {

}
