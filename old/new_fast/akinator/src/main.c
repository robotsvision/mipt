/**
 * @file main.c
 * @brief Точка входа. Обработка аргументов, запуск меню.
 *
 * @version 1.0.0
 * @date 21.12.24
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bintree.h"
#include "akinator.h"
#include "resources.h"

int main(int argc, char* argv[])
{
    bin_node_t* root = NULL;
    const char* filename = NULL;

    // Простейший разбор аргументов:
    // ./akinator -i data.aki
    if (argc == 3 && strcmp(argv[1], "-i") == 0) {
        filename = argv[2];
        root = load_tree_from_file(filename);
        // если не удалось загрузить, root = NULL
    } else {
        // Если нет 3 аргументов (или неправильные), выводим сообщение
        printf(akinator_get_res(AKINATOR_MSG_NO_ARGS_ENOUGH), argv[0]);
        // Не выходим — просто у нас нет файла
    }

    printf("%s", akinator_get_res(AKINATOR_MSG_INTRO));

    while (1) {
        printf("\n=== Меню ===\n");
        printf("1) Добавить элемент\n");
        printf("2) Играть в Акинатора\n");
        printf("3) Показать дерево (отладка)\n");
        printf("4) Сохранить и выйти\n");
        printf("%s", akinator_get_res(AKINATOR_MSG_MENU_SELECTION));

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            // Ошибка ввода
            break;
        }
        // Считываем \n
        getchar();

        switch (choice) {
            case 1:
                root = add_element_interactive(root);
                break;
            case 2:
                play_akinator(root);
                break;
            case 3:
                print_tree(root, 0);
                break;
            case 4:
                if (filename) {
                    // Сохраняем, если есть имя файла
                    save_tree_to_file(root, filename);
                }
                printf("%s", akinator_get_res(AKINATOR_MSG_QUIT));
                free_tree(root);
                return 0;
            default:
                printf("Неизвестный пункт меню.\n");
                break;
        }
    }

    // Если вышли по break — освобождаем дерево
    free_tree(root);
    return 0;
}
