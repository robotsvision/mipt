
#include <utils/graphviz.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*

digraph {
  // comment about next line of code
  B -> A [taillabel = "tail"]
  // comment 2
  D -> B
}

*/

static const struct {
    const char* name;
    const size_t size;
} _dotfile_formats[] = {
    [DOTFILE_GRAPH]     = { .name = "graph",    .size = 5 },
    [DOTFILE_DIGRAPH]   = { .name = "digraph",  .size = 7 }
};

dotfile_error_t dotfile_create(dotfile_t* file, dotfile_conf_t conf){
    if (file == NULL || conf.filename == NULL)
        return DOTFILE_ERROR_INVALID_ARG;

    FILE* dotfile = fopen(conf.filename, "w");

    if (dotfile == NULL)
        return DOTFILE_ERROR_FILE_OPEN;

    file->file = dotfile;
    file->format = conf.format;

    return DOTFILE_OK;
}


dotfile_error_t dotfile_write(dotfile_t* file, dotfile_obj_t* objects) {
    
    // Select format
    const char* label = _dotfile_formats[file->format].name;
    const size_t size = _dotfile_formats[file->format].size;

    

}


dotfile_error_t dotfile_close(dotfile_t* file) {
    if (fclose(file->file) == EOF)
        return DOTFILE_ERROR_FILE_CLOSE;
    return DOTFILE_OK;
}


