
/**
 * @file akinator.h
 * @brief Doubly linked list implementation.
 * 
 * @version 1.0.0
 * @date 21.12.24
 * @author Matvey Rybalkin
*/

#ifndef ALINATOR_RES_
#define ALINATOR_RES_

typedef enum {
    AKINATOR_MGS_INTRO,
    AKINATOR_MSG_NO_ARGS_ENOUGH,
    AKINATOR_MGS_MENU_SELECTION,
    AKINATOR_MSG_QUIT,

    _AKINATOR_NUM_RES,
} akinator_res_t;

extern const char* akinator_get_res(akinator_res_t msg);

#endif // ALINATOR_RES_