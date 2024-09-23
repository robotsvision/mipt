#ifndef ONEGIN_NATIVE_WINDOWS_MAP_IO_H_
#define ONEGIN_NATIVE_WINDOWS_MAP_IO_H_

/**************************************************************************//**
 * @file     map_io.h
 * @brief    Onegin App. Native / Windows / map_io.h
 * @version  V0.0.1
 * @date     23. Sep 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#include <windows.h>
#include <stdint.h>

typedef enum {
    OFILE_OK = 0x00,
    OFILE_ERROR = 0x01,
} oerror_t;

typedef struct {
    int64_t size;
    const void* data_handle;
    void* sys0_handle;  // aka mapHandle
    void* sys1_handle;  // aka fileHandle
} ofile_t;

/** 
 * @brief Opens a file by name and stores its data in file
 * 
 * 
 * @param[in] filename name of file in UTF-8 encode
 * @param[out] file file structure pointer
*/
extern oerror_t ofopen(const char filename[], ofile_t* file);

/** 
 * @brief Gets the pointer to file data
 *
 * @param[in] pointer target pointer
 * @param[in] file file structure pointer
*/
extern int ofget(char** pointer, ofile_t* file);

/** 
 * @brief Closes file and clear file structure
 *
 * @param[out] file file structure pointer
*/
extern int ofclose(ofile_t* file);

#endif // ONEGIN_NATIVE_WINDOWS_MAP_IO_H_

