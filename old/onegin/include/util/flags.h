#ifndef ONEGIN_UTILS_FLAGS_H_
#define ONEGIN_UTILS_FLAGS_H_

/**************************************************************************//**
 * @file     flags.h
 * @brief    MIPT repo. Onegin application. Utils / Flag handling.
 * @version  V0.0.1
 * @date     06. October 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#include <onegin/config.h>

typedef bool oflag_io_dir_t;
#define ONEGIN_INPUT false
#define ONEGIN_OUTPUT true
typedef enum {
    ONEGIN_FLAG_HELP,           // "--help"
    ONEGIN_FLAG_VERSION,        // "--version"

    ONEGIN_FLAG_SORT_FORWARD = 2,   // "--forward"
    ONEGIN_FLAG_SORT_REVERSE,   // "--reverse"
    ONEGIN_FLAG_ORIGINAL,       // "--original"

    ONEGIN_FLAG_INPUT,          // "-i"
    ONEGIN_FLAG_OUTPUT,         // "-o"

    ONEGIN_FLAG_INPUT_FILE,     // "file.txt"
    ONEGIN_FLAG_OUTPUT_FILE,    // "out.txt"

    ONEGIN_FLAG_INVALID = 0xFF, // Unrecognized flag
} onegin_flag_t;

#endif // ONEGIN_UTILS_FLAGS_H_