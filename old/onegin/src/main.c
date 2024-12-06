#include <onegin.h>

int main(const int argc, const char* argv[]) {
    oconf_t configuration;
    oerror_t error;
    error = onegin_configurate(&configuration, argc, argv);

    printf("Error: %d\n", error);

    printf(
"App = %d\n\
ifile = %s\n\
ofile = %s\n\
original = %d\n\
sort = %d\n",

    configuration.app,
    configuration.input_filename,
    configuration.output_filename,
    configuration.original,
    configuration.sort
);
    return EXIT_SUCCESS;
} 