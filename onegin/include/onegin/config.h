#ifndef ONEGIN_CONFIG_H_
#define ONEGIN_CONFIG_H_

/**************************************************************************//**
 * @file     config.h
 * @brief    MIPT repo. Onegin application. Application configuration.
 * @version  V0.0.1
 * @date     07. October 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/*************************************************************
* CONFIGURATION
************************************************************/

typedef enum {
    ONEGIN_APP_CONSOLE,
    ONEGIN_APP_GUI,
    ONEGIN_APP_SILENT,
} oapp_t;

typedef enum {
    ONEGIN_SORT_FORAWRD = 2,
    ONEGIN_SORT_REVERSE = 3,
} osort_t;

#define ONEGIN_UNDEFINED 0xFF

typedef struct {
    oapp_t app;
    char* input_filename;
    osort_t sort;
    char* output_filename;
    bool original;
} oconf_t;

typedef enum {
    ONEGIN_OK = 0,
    ONEGIN_ERROR = 1
} oerror_t;

/*************************************************************
* RELEASE - DEBUG MACROSES AND ASSERTS
************************************************************/

#define VERIFY(cond)    do {                                                                \
                            if (!(cond)) {                                                   \
                                fprintf(stderr, "VERIFY failed: %s\nFile: %s, Line: %d\n",   \
                                       #cond, __FILE__, __LINE__);                          \
                                exit(EXIT_FAILURE);                                          \
                            }                                                                \
                        } while (0)

#ifdef DEBUG
#define ASSERT(cond)    do {                                                                \
                            if (!(cond)) {                                                   \
                                fprintf(stderr, "VERIFY failed: %s\nFile: %s, Line: %d\n",   \
                                       #cond, __FILE__, __LINE__);                          \
                                exit(EXIT_FAILURE);                                          \
                            }                                                                \
                        } while (0)
#else
#define ASSERT(cond) ((void)0)
#endif

#endif // ONEGIN_CONFIG_H_