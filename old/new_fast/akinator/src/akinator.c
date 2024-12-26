/**
 * @file akinator.c
 *
 * @version 1.0.0
 * @date 21.12.24
 */

#include "akinator.h"
#include "resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void print_tree(const bin_node_t* root, int depth)
{
    if (!root) {
        for (int i = 0; i < depth; i++) printf("    ");
        printf("NULL\n");
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%s%s\n", root->text, root->is_leaf ? " (лист)" : "");
    
    print_tree(root->yes_child, depth + 1);
    print_tree(root->no_child,  depth + 1);
}

void play_akinator(bin_node_t* root)
{
    if (!root) {
        printf("%s", akinator_get_res(AKINATOR_MSG_GAME_EMPTY_TREE));
        return;
    }
    
    bin_node_t* current = root;
    while (1) {
        if (!current) {
            printf("NULL node...\n");
            return;
        }

        if (current->is_leaf) {
            printf(akinator_get_res(AKINATOR_MSG_GUESS), current->text);
            char ans[16];
            if (!fgets(ans, sizeof(ans), stdin)) {
                return;
            }
            if (tolower(ans[0]) == 'd') { 
                printf("%s", akinator_get_res(AKINATOR_MSG_GUESS_SUCCESS));
            } else {
                printf("%s", akinator_get_res(AKINATOR_MSG_GUESS_FAIL));
            }
            return;
        } else {
            printf(akinator_get_res(AKINATOR_MSG_CHAR_QUESTION), current->text);
            char ans[16];
            if (!fgets(ans, sizeof(ans), stdin)) {
                return;
            }
            
            if (tolower(ans[0]) == 'd') { // да
                if (current->yes_child) {
                    current = current->yes_child;
                } else {
                    printf("%s", akinator_get_res(AKINATOR_MSG_NO_YES_BRANCH));
                    return;
                }
            } else {
                if (current->no_child) {
                    current = current->no_child;
                } else {
                    printf("%s", akinator_get_res(AKINATOR_MSG_NO_NO_BRANCH));
                    return;
                }
            }
        }
    }
}

bin_node_t* add_element_interactive(bin_node_t* root)
{
    if (!root) {
        printf("%s", akinator_get_res(AKINATOR_MSG_ADD_NEW_ELEMENT));
        char buffer[256];
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            return NULL;
        }
        char* nl = strchr(buffer, '\n');
        if (nl) *nl = '\0';
        // Создаём узел (лист — ведь пока нет разделения на характеристику)
        root = create_node(buffer, 1);
        printf(akinator_get_res(AKINATOR_MSG_ADD_SUCCESS), buffer);
        return root;
    }

    bin_node_t* current = root;
    while (1) {
        if (current->is_leaf) {
            printf("Введите новую характеристику, которая отличает '%s' от нового объекта:\n> ",
                   current->text);
            char new_char[256];
            if (!fgets(new_char, sizeof(new_char), stdin)) {
                return root;
            }
            char* nl = strchr(new_char, '\n');
            if (nl) *nl = '\0';

            printf("%s", akinator_get_res(AKINATOR_MSG_ADD_NEW_ELEMENT));
            char new_obj[256];
            if (!fgets(new_obj, sizeof(new_obj), stdin)) {
                return root;
            }
            if ((nl = strchr(new_obj, '\n'))) {
                *nl = '\0';
            }

            printf("Если ответ 'да' на '%s', будет '%s'? (да/нет)\n> ", new_char, current->text);
            char ans[16];
            if (!fgets(ans, sizeof(ans), stdin)) {
                return root;
            }

            char* old_text = current->text;
            current->text = strdup(new_char);
            current->is_leaf = 0;

            bin_node_t* old_obj_node = create_node(old_text, 1); 
            free(old_text);

            bin_node_t* new_obj_node = create_node(new_obj, 1);

            if (tolower(ans[0]) == 'd') {
                current->yes_child = old_obj_node;
                current->no_child  = new_obj_node;
            } else {
                current->yes_child = new_obj_node;
                current->no_child  = old_obj_node;
            }
            printf(akinator_get_res(AKINATOR_MSG_ADD_SUCCESS), new_obj);
            return root;
        }
        
        printf(akinator_get_res(AKINATOR_MSG_CHAR_QUESTION), current->text);
        char answer[16];
        if (!fgets(answer, sizeof(answer), stdin)) {
            return root;
        }
        if (tolower(answer[0]) == 'd') {
            // Да
            if (!current->yes_child) {
                current->yes_child = create_node("", 1);
                current = current->yes_child; 
            } else {
                current = current->yes_child;
            }
        } else {
            // Нет
            if (!current->no_child) {
                current->no_child = create_node("", 1);
                current = current->no_child;
            } else {
                current = current->no_child;
            }
        }
    }
    return root;
}
