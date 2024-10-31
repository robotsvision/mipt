#ifndef ONEGIN_H_
#define ONEGIN_H_

/**************************************************************************//**
 * @file     onegin.h
 * @brief    MIPT repo. Onegin application. Main header file.
 * @version  V0.0.1
 * @date     06. October 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
#if __STDC_VERSION__ >= 201112L

// Standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Onegin libraries
#include <onegin/version.h>
#include <onegin/config.h>

#include <util/flags.h>
#include <util/files.h>
#include <util/sort.h>

/*************************************************************
* PUBLIC FUNCTIONS
************************************************************/

extern oerror_t onegin_configurate(oconf_t* conf, int argc, const char* argv[]);

extern int onegin_init(oconf_t config);

extern int onegin_sort(oconf_t config);

extern int onegin_print(oconf_t config);

extern void onegin_cleanup(oconf_t config);


#else
#   error "<onegin.h> ERROR: C language 2011 and above requires"
#endif

#ifdef __cplusplus
extern "C" }
#endif

#endif // ONEGIN_H_