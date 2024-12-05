#ifndef GRAPHVIZ_H_
#define GRAPHVIZ_H_

#include <process.h>
#include <stdio.h>

typedef enum {
    DOTFILE_OK,

    DOTFILE_ERROR_INVALID_ARG,

    DOTFILE_ERROR_FILE_OPEN,
    DOTFILE_ERROR_FILE_WRITE,
    DOTFILE_ERROR_FILE_CLOSE,

    DOTFILE_ERROR_INVALID_CHARACTER,
    DOTFILE_ERROR_BUFFER_EXCEEDED
} dotfile_error_t;

typedef enum {
    DOTFILE_GRAPH,
    DOTFILE_DIGRAPH
} dotfile_format_t;

/// @brief 
typedef struct {
    const char* content;
    const char* comment;
} dotfile_obj_t;

typedef struct {
    const char* filename;
    dotfile_format_t format;
} dotfile_conf_t;

typedef struct {
    char* _buffer;
    char* _ptr;
    size_t size;
} dotfile_buffer_t;

typedef struct {
    FILE* file;
    dotfile_format_t format;
    char* buffer;
} dotfile_t;

/**
 * @brief To create new dotfile.
 * 
 * To prepare, open or create a file to generate a dotfile.
 * 
 * @param[out] file output file structure
 * @param[in] filename name of the file
 * @returns Error code `dotfile_error_t` 
 * (`DOTFILE_ERROR_INVALID_ARG` `DOTFILE_ERROR_FILE_*`)
 */
extern dotfile_error_t dotfile_create(dotfile_t* file, dotfile_conf_t conf, size_t buffer);

/**
 * @brief To write objects to 
 */
extern dotfile_error_t dotfile_write(dotfile_t* file, dotfile_obj_t* objects);
extern dotfile_error_t dotfile_close(dotfile_t* file);

extern dotfile_buffer_t dotfile_buffer_create(size_t num_of_objs);
extern dotfile_error_t dotfile_buffer_append(dotfile_buffer_t* buffer, dotfile_obj_t new_object);
extern void dotfile_buffer_destroy(dotfile_buffer_t* buffer);

#endif // GRAPHVIZ_H_