

#include <differenciator.h>
#include <stdlib.h>

#define DIFF_DEFAULT_ALLOCATION_SIZE 4096UL

#define SIZE_(nmemb, size) (size * nmemb)

const char* expression = "1 + 20 / 4568 * 8568 + 564";

/**



/ (+ 1 20) ( + (* 4568 8568) 564)

+ 1 20
/

+ (* 4568 8568) 564


F :: = tok 

        /
     *     10
1230   x

       /
    1   +
      10  x

       +
     /   x
   1  10

       /
    1   cos
         x

       /
    1    cos
          +
        x   20

       +
    1    +
       2   +
          3  4 

       /
   cos   sin
   sin   cos
    x     x

       /


*/

void differenciate_expression(diff_tree_node_t* root) {

}

void _node_next(diff_tree_node_t* next) {
    if (next == NULL)
        return;
    
    if (next->data->type == DIFF_TREE_DATA_OPERATOR && next->data->content !=) {
        if (next->left != NULL &&)
            _node_next(next->left);

        if (next->right != NULL)
            _node_next(next->right);

    }
    
}

void get_expression(char* dest, diff_tree_node_t* root) {
    char* output_buffer = calloc(DIFF_DEFAULT_ALLOCATION_SIZE, sizeof(char));
    if (output_buffer == NULL)
        return 0;
    
    
}

void puts_expression(diff_tree_node_t* root, FILE* stream) {
    fputs(stream);
}
