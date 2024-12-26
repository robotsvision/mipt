#include <stdio.h>

typedef enum {
    DIFF_TREE_DATA_VARIABLE,
    DIFF_TREE_DATA_NUMBER,
    DIFF_TREE_DATA_OPERATOR,
} diff_tree_data_type_t;

typedef struct {
    union {
        char* variable;
        double DIFF_TREE_DATA_NUMBER;
    } content;
    diff_tree_data_type_t type;
} diff_tree_data_t;

typedef struct {
    diff_tree_data_t* data;
    diff_tree_node_t prev;
    diff_tree_node_t left;
    diff_tree_node_t right; 
} diff_tree_node_t;


void differenciate_expression(diff_tree_node_t* root);
void puts_expression(FILE* stream);
void get_expression(char* dest);
