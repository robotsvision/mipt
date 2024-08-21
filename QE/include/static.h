#ifndef QE_STATIC_H_
#define QE_STATIC_H_

/**************************************************************************//**
 * @file     static.h
 * @brief    MIPT project #1. Quadratic Equation Solver. Static mode header.
 * @version  V0.0.1
 * @date     21. August 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include specific libraries */
#include <llibs.h>

/* Public functions */

/**
 * @brief Execute static variant of the application.
 * 
 * @param[in] argc argument counter
 * @param[in] argv argument values 
 */
extern void qe_static(lu32 argc, lc8* argv[]);

#endif // QE_STATIC_H_