#ifndef ONEGIN_H_
#define ONEGIN_H_

/**************************************************************************//**
 * @file     onegin.h
 * @brief    Onegin Application main header. MIPT task 1.
 * @version  V0.3.0
 * @date     30. Sep 2024
 * @author   Matvey Rybalkin
******************************************************************************/

#ifndef __cplusplus

#define USE_ELLIPSE_MAIN_ARGS_SIGNATURE // To use application with aruments
#define USE_ELIX                        // To use GUI libraries in llibs.h
#include <llibs.h>  // Main Ellipse (llibs) framework header.

#define ONEGIN_VERSION  200UL
#define ONEGIN_VERSION_CSTR (cstr_t)("0.2.0")

/**
 * @brief Launches the Onegin application in graphical user interface (GUI) mode.
 *
 * This function starts the Onegin application with a graphical interface, 
 * allowing the user to interact with the program through visual elements.
 * 
 * @param[in] args Structure `app_args_t` containing command line arguments and parameters 
 * required for the application to operate.
 */
extern void onegin_gui(app_args_t args);

/**
 * @brief Launches the Onegin application in console mode.
 *
 * This function runs the Onegin application in console mode, enabling 
 * command-line interaction without a graphical interface.
 * 
 * @param[in] args Structure `app_args_t` containing command line arguments and parameters 
 * necessary for the application.
 */
extern void onegin_console(app_args_t args);

/**
 * @brief Launches the Onegin application in quiet console mode.
 *
 * This function executes the Onegin application in console mode with reduced output, 
 * minimizing console messages for a quieter run. It is ideal for background execution 
 * or when minimal feedback is required.
 * 
 * @param[in] args Structure `app_args_t` containing command line arguments and parameters 
 * essential for the application.
 */
extern void onegin_console_quite(app_args_t args);


#else
#   error "[onegin.h]: Onegin Application requires pure C, not C++"
#endif


#endif // ONEGIN_H_