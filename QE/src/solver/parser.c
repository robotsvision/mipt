/* Include specific libraries */
#include "solver/parser.h"

/* Limits and Math */
#include <float.h>
#include <math.h>

// from Lena tokenizer ->

/* ---------------- Trash characters ---------------- */
static const lc trash_chars[] = {
    Y(' '), Y('\t')
};
static lbool is_trash(lc ch) {
    for (lu8 i = 0; i < 2; ++i) {
        if (ch == trash_chars[i])
            return true;
    }
    return false;
}
static void pass_trash(lc** expr) {
    while (is_trash(**expr)) {
        (*expr)++;
    }
}

/* Macroses */
#define INVALID_LEVEL (lu8)(0xFF)
#define IS_EOF(a) (a == Y('\0'))
#define IS_DIGIT(a) (Y('0') <= a  && a <= Y('9'))
#define IS_OPERATOR_CHAR(a) (a == Y('+')\
                            ||(a == Y('-'))\
                            ||(a == Y('*'))\
                            ||(a == Y('/')))

// end lena tokenizer <-

/* --------- Parse numbers --------- */

#define PARSE_NUMBER_INVALID_FORMAT (lf32)(NAN)
#define PARSE_NUMBER_LIMIT_EXEEDED  (lf32)(INFINITY)

// temporary solution
#include <stdio.h>
lf32 X_to_lf32(lc* expr) {
    static lf32 result = NAN;
    sscanf((char* )(expr), "%lf", &result);
    return result;
}
lf32 parse_number(lc** expr, lbool decimal) {
    /* Using LF32 type limits */
    lu16 ans = DBL_MAX_10_EXP + 2;

    /* Variables */
    lbool is_decimal = false;
    lc* num_ptr = (*expr);

    /* Parse number */

    while (!IS_EOF((**expr))) {
        
        /* Test limits */
        if (!ans) {
            return PARSE_NUMBER_LIMIT_EXEEDED;
        }

        /* Decimal */
        if ((**expr) == '.') {
            if (is_decimal == false) {
                is_decimal = true;
                ++(*expr);
                if (!decimal) {
                    return PARSE_NUMBER_INVALID_FORMAT;
                }
            } else {                
                return PARSE_NUMBER_INVALID_FORMAT; 
            }
        }

        if (IS_DIGIT((**expr))) {
            ++(*expr); --ans;
        } else {
            /* Break */
            break;
        }
    } 
    
    /* After all checkups we can transform this number */
    return X_to_lf32(num_ptr);
}


/* Minimal buffer (can be extended) */
static qe_parser_node nodes[4];

/**
 * static examples of use:
 *      qe -s "2x^2 + 4x - 2 = 0" -o "answer.txt"
 * 
 *  Переменные не могут занимать больше одного символа
 */

lerr qe_parse(lc* expr, lu64* num,  qe_parser_node* nodes) {
    
    while (!IS_EOF((*expr))) {
    }
}