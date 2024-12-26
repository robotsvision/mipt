
/**
 * @file bintree.h
 *
 * @version 1.0.0
 * @date 21.12.24
 */

#ifndef BINTREE_H_
#define BINTREE_H_

typedef struct bin_node {
    char* text;
    int   is_leaf;
    struct bin_node* yes_child;
    struct bin_node* no_child;
} bin_node_t;

bin_node_t* create_node(const char* text, int is_leaf);
void free_tree(bin_node_t* root);
bin_node_t* load_tree_from_file(const char* filename);
void save_tree_to_file(const bin_node_t* root, const char* filename);

#endif // BINTREE_H_
