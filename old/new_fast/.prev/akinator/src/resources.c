#include <akinator.h>
#include <resources.h>

const char* _akinator_resources[] = {
    [AKINATOR_MSG_NO_ARGS_ENOUGH] =
    "┌───────────────────────────────────────┐"
    "│                                       │"
    "│     ✓ Akinator не требует флагов!     │"
    "│                                       │"
    "└───────────────────────────────────────┘",

    [AKINATOR_MGS_INTRO] =
    "╭───────────────────────────────────────╮"
    "│               AKINATOR                │"
    "╰───────────────────────────────────────╯",


    [AKINATOR_MGS_MENU_SELECTION] =
    "[1] ▶ Начать игру"
    "[2] ▶ Настройки"
    "[3] ▶ Выйти",

    [AKINATOR_MSG_QUIT] =
    "[y/n] ▶ Вы уверены что хотите выйти?",

};

const char* akinator_get_res(akinator_res_t res) {
    return _akinator_resources[(int)(res)];
}
