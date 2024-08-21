/* Include specific libraries */
#include "static.h"
#include "qe_config.h"

/* Parser */
#include "parser/parser.h"

/* Public functions */


void qe_static(lu32 argc, lc8* argv[]) {
    lu64 num = 0;
    qe_parser_node node_buffer[1];
    qe_parse(argv[1], &num, node_buffer);
    return;
}