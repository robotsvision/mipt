#include <util/logs.h>

#if DEBUG

#include <stdarg.h>

uint8_t _onegin_log_level = 0;
FILE* _onegin_log_file = NULL;

void onegin_log_stdout_init(onegin_log_level_t level){
    _onegin_log_file = stdout;
    _onegin_log_level = level;
}

void onegin_log_finit(const char* filename, onegin_log_level_t level){
    _onegin_log_file = fopen(filename, "w");
    _onegin_log_level = level;
}

void onegin_log_deinit(void){
    fclose(_onegin_log_file);
}

void onegin_log(onegin_log_level_t level, const char* format, ...){
    if (_onegin_log_level <= level) {
        va_list args;
        va_start(args, format);
        vfprintf(_onegin_log_file, format, args);
        va_end(args);
    }
}

void assert(bool condition, int exit_code, const char* format, ...) {
    if (condition) {
        va_list args;
        va_start(args, format);
        vfprintf(_onegin_log_file, format, args);
        va_end(args);
        exit(exit_code);
    }
}

#else

// Empty functions 

void onegin_log_stdout_init(
    __attribute__((unused)) onegin_log_level_t level){}

void onegin_log_finit(
    __attribute__((unused)) const char* filename, 
    __attribute__((unused)) onegin_log_level_t level){}

void onegin_log_deinit(void){}

void onegin_log(
    __attribute__((unused)) onegin_log_level_t level, 
    __attribute__((unused)) const char* format, 
    ...){}

void assert(
    __attribute__((unused)) bool condition, 
    __attribute__((unused)) int exit_code, 
    __attribute__((unused)) const char* format, 
    ...) {}


#endif 
