#include <akinator.h>

int main(int argc, char* argv[]) {
    // Указатель на корень дерева
    TreeNode* root = NULL;

    // Парсим аргументы
    if (argc == 3 && strcmp(argv[1], "-i") == 0) {
        // argv[2] — это имя файла
        root = loadTreeFromFile(argv[2]);
        if (!root) {
            printf("Не удалось загрузить дерево из файла '%s'.\n", argv[2]);
            // Можно продолжать, но root = NULL, значит у нас пустое дерево
        }
    } else {
        printf("Запуск без параметров или с некорректными.\n");
        printf("Использование: %s -i data.aki\n", argv[0]);
        printf("Будет создано пустое дерево.\n");
    }

    // Основной цикл программы
    while (1) {
        printf("\n=== Главное меню ===\n");
        printf("1) Добавить элемент\n");
        printf("2) Играть в Акинатора\n");
        printf("3) Показать дерево (для отладки)\n");
        printf("4) Сохранить и выйти\n");
        printf("Ваш выбор: ");

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода.\n");
            break;
        }
        getchar(); // считываем '\n'

        switch (choice) {
            case 1:
                addElementInteractive(root);
                break;
            case 2:
                playAkinator(root);
                break;
            case 3:
                printTree(root, 0);
                break;
            case 4: {
                // Сохраняем дерево (если root != NULL)
                if (root && argc == 3 && strcmp(argv[1], "-i") == 0) {
                    FILE* fp = fopen(argv[2], "w");
                    if (!fp) {
                        printf("Ошибка: не удалось открыть файл '%s' для записи.\n", argv[2]);
                    } else {
                        saveTreeToFile(root, fp, 0);
                        fclose(fp);
                        printf("Дерево сохранено в файл '%s'.\n", argv[2]);
                    }
                }
                freeTree(root);
                return 0;
            }
            default:
                printf("Неизвестная опция.\n");
                break;
        }
    }
    freeTree(root);
    return 0;
}
