#ifndef ONEGIN_UTILS_FILES_H_
#define ONEGIN_UTILS_FILES_H_

/**************************************************************************//**
 * @file     files.h
 * @brief    MIPT repo. Onegin application. Utils / Files.
 * @version  V0.0.1
 * @date     06. October 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#include <util/types.h>

typedef enum {
    OFILE_ENCODE_ASCII,
    OFILE_ENCODE_UTF8,
    OFILE_ENCODE_UTF16LE,
    OFILE_ENCODE_UTF16BE,

    OFILE_ENCODE_UNRECOGNIZED = 0xFF,
} ofile_encode_t;

#ifdef WIN32

#include <windows.h>

typedef struct {
    ofile_encode_t encode;
    
} ofile_t;

#else

typedef struct {
    ofile_encode_t encode;
    void* data;
    size_t size;
} ofile_t;

#endif 

/*************************************************************
* PUBLIC FUNCTIONS
************************************************************/

/**
 * @brief To open file and get file data and encode.
 * 
 * @param[out] file handler of the file
 * @param[in] filename name of the file
 * @returns error code
 */
extern int ofopen(ofile_t* file, const char* filename);

/**
 * @brief To cloes file and free memory.
 * 
 * @param[out] file handler of the file
 * @param[in] data file data pointer
 */
extern void oclose(ofile_t* file, void* data);


#endif // ONEGIN_UTILS_FILES_H_