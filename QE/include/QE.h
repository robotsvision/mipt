#ifndef QE_H_
#define QE_H_

/**************************************************************************//**
 * @file     QE.h
 * @brief    MIPT project #1. Quadratic Equation Solver.
 * @version  V0.0.1
 * @date     20. August 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include Llibs framework */
#include <llibs.h>

/* Main QE functions */

/**
 *  @brief QE application main function.
 * 
 *  Must be called in `lmain()` funnction.
 * 
 *  @param[in] argc argument counter.
 *  @param[in] argv argument variables.
 *  @returns application status
 * 
 */
extern lm qe_solve(lu32 argc, lc8* argv[]);

#endif // QE_H_