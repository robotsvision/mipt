
/**
 * @file resources.h
 * 
 * @version 1.0.0
 * @date 21.12.24
 */

#ifndef AKINATOR_RESOURCES_H_
#define AKINATOR_RESOURCES_H_

typedef enum {
    AKINATOR_MSG_NO_ARGS_ENOUGH = 0, ///< Not enough arguments
    AKINATOR_MSG_INTRO, ///< Message on startup
    AKINATOR_MSG_MENU_SELECTION, ///< Message to prompt for menu item selection
    AKINATOR_MSG_QUIT, ///< Message before exiting
    AKINATOR_MSG_GAME_EMPTY_TREE, ///< Message if tree is empty
    AKINATOR_MSG_GUESS, ///< Message "Is this %s? (yes/no)"
    AKINATOR_MSG_GUESS_SUCCESS, ///< Hurray! I guessed right!
    AKINATOR_MSG_GUESS_FAIL, ///< Didn't guess...
    AKINATOR_MSG_CHAR_QUESTION, ///< Message "%s? (yes/no)"
    AKINATOR_MSG_NO_YES_BRANCH, ///< No yes-branch
    AKINATOR_MSG_NO_NO_BRANCH, ///< No no-branch

    AKINATOR_MSG_ADD_NEW_ELEMENT, ///< "Enter the name of the new element"
    AKINATOR_MSG_ADD_SUCCESS, ///< "Element '%s' has been successfully added!"

    _AKINATOR_NUM_RES, ///< Technical counter
} akinator_res_t;

const char* akinator_get_res(akinator_res_t msg);

#endif // AKINATOR_RESOURCES_H_
