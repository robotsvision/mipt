#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node {
    const char* condition;
    struct node* prev;
    struct node* left_yes;
    struct node* right_no;
} node_t;

node_t* create_node(const char* condition) {
    node_t* new_node = calloc(1, sizeof(node_t));
    new_node->condition = condition;
    new_node->left_yes = NULL;
    new_node->right_no = NULL;
    new_node->prev = NULL;
    return new_node;
}

void node_add(node_t* dest, node_t* new_node, bool is_yes_branch) {
    if (dest == NULL || new_node == NULL)
        return;
    
    new_node->prev = dest;
    if (is_yes_branch) {
        dest->left_yes = new_node;
    } else {
        dest->right_no = new_node;
    }
}

void node_print(node_t* node) {
    if (node == NULL)
        return;
    
    printf("\nУсловие: %s\n", node->condition);

    if (node->left_yes != NULL) {
        printf("Если да, то: ");
        node_print(node->left_yes);
    }

    if (node->right_no != NULL) {
        printf("Если нет, то: ");
        node_print(node->right_no);
    }
}

void node_graph(node_t* node, FILE* file) {
    if (node == NULL)
        return;

    if (node->left_yes != NULL) {
        fprintf(file, "    \"%s\" -> \"%s\" [label=\"yes\"];\n", node->condition, node->left_yes->condition);
        node_graph(node->left_yes, file);
    }

    if (node->right_no != NULL) {
        fprintf(file, "    \"%s\" -> \"%s\" [label=\"no\"];\n", node->condition, node->right_no->condition);
        node_graph(node->right_no, file);
    }
}

void generate_graph(node_t* root) {
    FILE* file = fopen("tree.dot", "w");
    if (file == NULL) {
        perror("Не удалось создать файл tree.dot");
        return;
    }
    fprintf(file, "digraph Tree {\n");
    fprintf(file, "    node [shape=ellipse];\n");

    node_graph(root, file);

    fprintf(file, "}\n");
    fclose(file);

    system("dot -Tpng tree.dot -o tree.png");
    printf("Граф дерева сгенерирован и сохранен в tree.png\n");
}


int main(void) {
    node_t* root = create_node("whats");

    node_t* node1 = create_node("Условие 1");
    node_t* node2 = create_node("Условие 2");

    node_add(root, node1, true);
    node_add(root, node2, false);

    printf("Дерево условий:\n");
    node_print(root);

    free(root);
    free(node1);
    free(node2);

    return EXIT_SUCCESS;
}
