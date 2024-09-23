#ifndef ONEGIN_UTIL_FLAGS_ENUM_H_
#define ONEGIN_UTIL_FLAGS_ENUM_H_

/**************************************************************************//**
 * @file     flags.enum.h
 * @brief    Onegin App. Util / Working with flags. Enumiration.
 * @version  V0.0.1
 * @date     17. Sep 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

typedef enum {
    ONEGIN_FLAGS_HELP,
    ONEGIN_FLAGS_SOURCE,
    ONEGIN_FLAGS_OUTPUT,

    ONEGIN_FLAGS_SORT_PREFIX,
    ONEGIN_FLAGS_SORT_POSTFIX,

    ONEGIN_VERSION,
    ONEGIN_VERSION_EXTENDED,
} onegin_flags_t;


#endif // ONEGIN_UTIL_FLAGS_ENUM_H_