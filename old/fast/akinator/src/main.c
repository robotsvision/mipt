#include <akinator.h>
#include <stdbool.h>

typedef const char* node_data_t;

typedef struct {
    node_data_t data;
    struct node_t* prev;
    struct node_t* left;
    struct node_t* right;
} node_t;

bool is_leave(node_t* node) {
    if (node == NULL || (node->left != NULL || node->right != NULL)) {
        return false;
    }
}

void nodes_go_around(node_t* root, bool(*handle)(node_data_t, ...)) {
    if (root == NULL || root->data == NULL)
        return;
    
    if (!handle(root->data))
        return;

    if (root->left != NULL)
        nodes_go_around(root->left, handle);

    if (root->right != NULL)
        nodes_go_around(root->right, handle);
}

bool _nodes_handle_print(node_data_t data, ...) {
    return (bool)(puts(data) != EOF);
}

void nodes_print(node_t* root) {
    nodes_go_around(root, _nodes_handle_print);
}

void _nodes_get_info_rec(node_t* node) {
    if (node->prev == NULL)
        return;

    struct node_t* prev = node->prev;

    if (prev->left == node){
        puts("True: ");
    } else {
        puts("False: ");
    } 
    puts(prev->data);

    _nodes_get_info_rec(prev);
}

void nodes_get_info(node_t* node) {
    if (node == NULL || !is_leave(node))
        return;

    _nodes_get_info_rec(node);
}

// after_this_node is left or right node_t in structure
void nodes_add(node_t** after_this_node, node_t* new_node) {
    (*after_this_node) = new_node;
}

void _nodes_compare(node_data_t data) {
    if (data == )
}

void nodes_find(node_data_t data, node_t* root) {

}


int main(void) {
    
}