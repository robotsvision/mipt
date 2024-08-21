/* Include specific libraries */
#include <QE.h>

/* Private functions and types */
#include "interactive.h"
#include "static.h"

/* ----------------- Secondary functions ----------------- */

#define IS_NO_INPUT_FLAGS(a) (lbool)(a <= 1)

/* ----------------- Main functions ----------------- */

/* Public functions */

lm qe_solve(lu32 argc, lc8* argv[]) {
    if (llibs_init() != L_OK) { return L_EXIT_FAILURE; }
    if (IS_NO_INPUT_FLAGS(argc)) {
        qe_interactive();
    } else {
        qe_static(argc, argv);
    }
    return L_EXIT_SUCCESS;
}