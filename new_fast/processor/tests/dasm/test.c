#include <disassembler.h>

int main(void) {
    cpu_conf_t configuration = {
        .R_size = REGISTER_AREA_SIZE(16),
        .RAM_size = 4096,
    };
}