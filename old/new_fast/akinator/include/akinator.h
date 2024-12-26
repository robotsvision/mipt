/**
 * @file akinator.h
 *
 * @version 1.0.0
 * @date 21.12.24
 */

#ifndef AKINATOR_H_
#define AKINATOR_H_

#include "bintree.h"

void play_akinator(bin_node_t* root);
bin_node_t* add_element_interactive(bin_node_t* root);
void print_tree(const bin_node_t* root, int depth);

#endif // AKINATOR_H_
