/**
 * @file bintree.c
 * @version 1.0.0
 * 
 * @date 21.12.24
 */

#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bin_node_t* create_node(const char* text, int is_leaf) {
    bin_node_t* node = (bin_node_t*)malloc(sizeof(bin_node_t));
    if (!node) {
        fprintf(stderr, "Ошибка: не удалось выделить память под узел.\n");
        return NULL;
    }
    node->text = strdup(text);
    node->is_leaf = is_leaf;
    node->yes_child = NULL;
    node->no_child = NULL;
    return node;
}

void free_tree(bin_node_t* root) {
    if (!root) return;
    free_tree(root->yes_child);
    free_tree(root->no_child);
    free(root->text);
    free(root);
}

static void save_node(const bin_node_t* node, FILE* fp) {
    if (!node) {
        fprintf(fp, "NULL\n");
        return;
    }
    // 1) text
    fprintf(fp, "%s\n", node->text);
    // 2) is_leaf
    fprintf(fp, "%d\n", node->is_leaf);
    // 3) yes_child
    save_node(node->yes_child, fp);
    // 4) no_child
    save_node(node->no_child, fp);
}

void save_tree_to_file(const bin_node_t* root, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Ошибка: не удалось открыть файл '%s' для записи.\n", filename);
        return;
    }
    save_node(root, fp);
    fclose(fp);
}

static bin_node_t* load_node(FILE* fp) {
    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), fp)) {
        return NULL;
    }
    char* nl = strchr(buffer, '\n');
    if (nl) *nl = '\0';

    if (strcmp(buffer, "NULL") == 0) {
        return NULL;
    }
    char* text = strdup(buffer);

    if (!fgets(buffer, sizeof(buffer), fp)) {
        free(text);
        return NULL;
    }
    if ((nl = strchr(buffer, '\n'))) {
        *nl = '\0';
    }
    int is_leaf = atoi(buffer);

    bin_node_t* node = create_node(text, is_leaf);
    free(text);

    node->yes_child = load_node(fp);
    node->no_child = load_node(fp);
    return node;
}

bin_node_t* load_tree_from_file(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Ошибка: не удалось открыть файл '%s'.\n", filename);
        return NULL;
    }

    bin_node_t* root = load_node(fp);
    fclose(fp);
    return root;
}
