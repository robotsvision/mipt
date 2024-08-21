#ifndef QE_ERRORS_H_
#define QE_ERRORS_H_

/**************************************************************************//**
 * @file     static.h
 * @brief    MIPT project #1. Quadratic Equation Solver. Errors header.
 * @version  V0.0.1
 * @date     21. August 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include Llibs framework */
#include <llibs.h>

/* Error messages are here */

typedef enum {

    /* ---------- Expression errors ---------- */
    QE_ERROR_E_INVALID_SYMBOL,      // example: "qe -s "&" "
    QE_ERROR_E_UNFINISHED_EXPR,     // example: "qe -s "4x^2+12x-4="
    QE_ERROR_E_INVALID_VAR_NAME,    // example: "qe -s "4x^2+12y-4=0" (x and y)
    QE_ERROR_E_INVALID_SEQUENCE,    // example: "qe -s "4x^2+12x-4="
    QE_ERROR_E_POWER_EXEEDED,       // example: "qe -s "4x^5+12x-4="

} qe_error_expr_t;


typedef enum {

    /* -------------- Math errors ------------- */
    QE_ERROR_M_DIV0,                // example: when you need to divide a number by zero

} qe_error_math_t;

extern lc* qe_error_expr_buffer[];

/** Error message signature:
 * 
 *  qe -s "4x^2 + 25y - 4 = 0"
 * 
 */


#endif // QE_ERRORS_H_