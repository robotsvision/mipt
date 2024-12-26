
/**
 * @file resources.c
 *
 * @version 1.0.0
 * @date 21.12.24
 */

#include "resources.h"

static const char* _akinator_resources[] = {
    [AKINATOR_MSG_NO_ARGS_ENOUGH]  = "Недостаточно аргументов. Использование: %s -i <filename>\n",
    [AKINATOR_MSG_INTRO]           = "=== Добро пожаловать в Акинатор! ===\n",
    [AKINATOR_MSG_MENU_SELECTION]  = "Введите номер пункта меню: ",
    [AKINATOR_MSG_QUIT]            = "Выход из программы...\n",
    [AKINATOR_MSG_GAME_EMPTY_TREE] = "Дерево пустое! Сначала добавьте элементы.\n",
    [AKINATOR_MSG_GUESS]           = "Вы загадали: %s? (да/нет)\n> ",
    [AKINATOR_MSG_GUESS_SUCCESS]   = "Ура! Я угадал!\n",
    [AKINATOR_MSG_GUESS_FAIL]      = "Не угадал... Возможно, нужно дообучить.\n",
    [AKINATOR_MSG_CHAR_QUESTION]   = "%s? (да/нет)\n> ",
    [AKINATOR_MSG_NO_YES_BRANCH]   = "Нет «да»-ветви. Не могу продолжать.\n",
    [AKINATOR_MSG_NO_NO_BRANCH]    = "Нет «нет»-ветви. Не могу продолжать.\n",
    [AKINATOR_MSG_ADD_NEW_ELEMENT] = "Введите название нового элемента:\n> ",
    [AKINATOR_MSG_ADD_SUCCESS]     = "Элемент '%s' успешно добавлен!\n",
};

const char* akinator_get_res(akinator_res_t msg) {
    if (msg < 0 || msg >= _AKINATOR_NUM_RES) {
        return "INVALID RESOURCE INDEX";
    }
    return _akinator_resources[msg];
}
