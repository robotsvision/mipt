#include <onegin.h>
#include <util/flags.h>

#define ONEGIN_ARG_TOO_SHORT    0x02
#define ONEGIN_ARG_INVALID      0x03

const char* _flag_map[] = {
    [ONEGIN_FLAG_HELP]          = "help",
    [ONEGIN_FLAG_VERSION]       = "version",
    [ONEGIN_FLAG_SORT_FORWARD]  = "forward",
    [ONEGIN_FLAG_SORT_REVERSE]  = "reverse",
    [ONEGIN_FLAG_ORIGINAL]      = "original",
};

const size_t _flag_map_len = 5UL;

void _onegin_help(void);
void _onegin_version(void);

static inline bool is_double_dash(const char* flag) {
    return flag[0] == '-' && flag[1] == '-';
}

static inline bool is_single_dash(const char* flag) {
    return flag[0] == '-';
}

oerror_t onegin_configurate(oconf_t* conf, int argc, const char* argv[]) {
    ASSERT(conf != NULL);
    
    (*conf) = (oconf_t){
        .input_filename = NULL,
        .sort = ONEGIN_UNDEFINED,
        .output_filename = NULL,
        .original = false,
    };

    if (argc <= 1) {
        conf->app = ONEGIN_APP_GUI;
        return ONEGIN_OK;
    } else {
        
        for (int i = 1; i < argc; ++i) {
            static oflag_io_dir_t dir = ONEGIN_INPUT;
            char* flag = argv[i];
            size_t len = strlen(flag);
            if (len < 3) {
                return ONEGIN_ARG_TOO_SHORT;
            }
            if (is_double_dash(flag)) {
                for (size_t i = 0; i < _flag_map_len; ++i) {
                    if (strcmp(flag + 2, _flag_map[i]) == 0) {
                        switch (i) {
                        case ONEGIN_FLAG_HELP:
                            _onegin_version();
                            exit(EXIT_SUCCESS);
                        case ONEGIN_FLAG_VERSION:
                            _onegin_version();
                            exit(EXIT_SUCCESS);
                        case ONEGIN_FLAG_ORIGINAL:
                            conf->original = true;
                            break;
                        default: {
                            conf->sort = (osort_t)i;
                        }
                        }
                    }
                }
            } else if (is_single_dash(flag)) {
                switch (flag[1]) {
                case 'o':
                    dir = ONEGIN_OUTPUT;
                    break;
                case 'i':
                    dir = ONEGIN_INPUT;
                    break;
                default:
                    return ONEGIN_ARG_INVALID;
                }
            } else {
                // it must be a file
                if (dir == ONEGIN_INPUT) {
                    conf->input_filename  = argv[i];
                } else {
                    conf->output_filename = argv[i];
                }
            }
        }
    }
    return ONEGIN_OK;
}

#undef IS_DOUBLE_DASH
#undef IS_SINGLE_DASH

const char* _help_message =
"Onegin Application - Text sorting tool inspired by the classic text 'Eugene Onegin'\n\n"
"Usage:\n"
"  onegin [options] [input_file] [output_file]\n\n"
"Options:\n"
"  --help                   Show this help message and exit.\n"
"  --version                Show version information and exit.\n"
"  --forward                Sort lines of text in forward alphabetical order.\n"
"  --reverse                Sort lines of text in reverse alphabetical order.\n"
"  --original               Output the text in its original order without sorting.\n"
"  --interactive            Run the application in interactive console mode.\n"
"  -i <file>                Specify the input file (e.g., -i input.txt).\n"
"  -o <file>                Specify the output file (e.g., -o output.txt).\n\n"
"Notes:\n"
"  - If no options are provided, the application runs in GUI mode.\n"
"  - The input file should contain the text to be sorted, and the output file\n"
"    will contain the sorted or original version of the text.\n"
"  - The interactive mode allows you to specify options dynamically.\n\n"
"Examples:\n"
"  onegin -i input.txt -o sorted.txt --forward\n"
"      Sort the lines of 'input.txt' in forward alphabetical order and\n"
"      save the result to 'sorted.txt'.\n"
"  onegin --interactive\n"
"      Run the application in interactive mode to select options dynamically.\n";



void _onegin_help(void) {
    puts(_help_message);
}

void _onegin_version(void) {
    printf (
"Onegin. Version: %s\n\
License: Unlicense.\n\
Read 'license' file for more", 
    ONEGIN_VERSION_CSTR
    );
}
