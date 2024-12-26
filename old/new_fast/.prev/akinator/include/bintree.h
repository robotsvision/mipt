
/**
 * @file bintree.h
 * @brief Basic binary tree library for implementing 
 * all necessary functionality and macros.
 * 
 * @version 1.0.0
 * @date 21.12.24
 * @author Matvey Rybalkin
*/

#ifndef AKINATOR_BINTREE_H_
#define AKINATOR_BINTREE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node {
    const char* data;
    struct node* prev;
    struct node* left;
    struct node* right;
} node_t;

typedef node_t tree_t;

extern node_t* node_create(const char* value);
extern void node_delete(node_t* node, bool subtree);

extern void tree_print(tree_t* root_node, FILE* stream);
extern node_t* tree_search(tree_t* root_node, const char* value);

#endif // AKINATOR_BINTREE_H_
