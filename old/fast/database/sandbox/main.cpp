#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Это может быть небинарное дерево

typedef     char* node_data_t;
#define NODE_ROOT_DATA (char*)"root"

typedef struct node {
    node_data_t data;
    size_t num_of_connections;
    struct node** connections;
} node_t;

// выводит дерево с начала
void print_node(node_t nodes[]) {
    if (nodes == NULL)
        return;

    if (nodes->num_of_connections == 0 || nodes->data == NULL)
        return;

    for (size_t i = 0; i < nodes->num_of_connections; ++i) {
        print_node(nodes->connections[i]);
    } 
}

void nodes_init(node_t nodes[]) {

    if (nodes == NULL)
        return;
    
    node_t* new_nodes = (node_t *)(calloc(1, sizeof(node_t)));

    if (new_nodes == NULL)
        return;

    // create root node

    new_nodes[0].connections = NULL;
    new_nodes[0].num_of_connections = 0;
    new_nodes[0].data = NODE_ROOT_DATA;

    nodes = new_nodes;
}

void node_add(node_t* to_node, node_t new_node, node_data_t data) {
    if (to_node == NULL)
        return;
    
    to_node->connections[to_node->num_of_connections + 1] = (node_t *)calloc(1, sizeof(node_t));

    if (to_node->connections == NULL)
        return;
    
    

}

void nodes_destroy(node_t* nodes) {
    if (nodes == NULL)
        return;

    
}

int main(void) {
    node_t nodes[10];
    //setlocale(LC_ALL, "ru_RU.UTF-8");
    printf("Привет Мир!");
    return 0;
}