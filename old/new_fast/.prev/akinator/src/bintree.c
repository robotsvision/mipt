#include <bintree.h>
#include <stdint.h>
#include <string.h>

node_t* node_create(const char* value) {
    node_t* new_node = calloc(1, sizeof(node_t));

    if (!new_node || !value)
        return NULL;

    new_node->data = strdup(value);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->prev = NULL;
    return new_node;
}

void node_delete(node_t* node, bool subtree) {
    if (!node)
        return;
    
    if (!subtree) {
        free(node);
    } else {
        node_delete(node->left, true);
        node_delete(node->right, true);
        free(node);
    }
}

static void _tree_print(tree_t* root_node, FILE* stream, uint32_t depth) {
    if (!root_node)
        return;

    for (uint32_t i = 0; i < depth; ++i)
        fputc('\t', stream);

    fputs(root_node->data, stream);
    fputc('\n', stream);

    _tree_print(root_node->left, stream, depth + 1);
    _tree_print(root_node->right, stream, depth + 1);
}

void tree_print(tree_t* root_node, FILE* stream) {
    if (!root_node || !stream)
        return;
    
    _tree_print(root_node, stream, 0U);
}

static void _tree_search(node_t* node, const char* value, node_t** ans) {
    if (!node)
        return;

    if (strcmp(value, node->data) == 0) {
        (*ans) = node;
        return;
    }

    _tree_search(node->left, value, ans);
    _tree_search(node->right, value, ans);
}

node_t* tree_search(tree_t* root_node, const char* value) {
    node_t* answer = NULL;
    _tree_search((node_t*)(root_node), value, &answer);
    return answer;
}
