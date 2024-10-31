/**
 * Быстрый Онегин.
 * 
 * onegin (или onegin --interactive)            => Интерактивный режим
 * onegin --quiet -i onegin.txt -o out.txt     => Тихий режим приложения
 *
 * Ограничения:
 *  *   Работает только с ASCII или любой другой однобайтовой кодировкой.
 *  *   Могут быть проблемы при работе с большими файлами, т.к. не используется виртуализация памяти
 */

/**
 *  Замечания:
 *      Некрасивая работа с очисткой выделенной памяти.
 *      Работает только на одной ОС.
 *      Не все файлы может принять и корректно сортировать (например ковычки и т.п символы)
 *      ТОЛЬКО С ИНТЕРАКТИВНЫМ РЕЖИМОМ
 */


/**************************************************************************************************/

#ifdef __linux__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/////////////////////////////////////////////
/////////// Конфигурация проекта //////////// 
/////////////////////////////////////////////

#define MIN_FILE_LEN 4
#define SCANF_INPUT_BUFFER_FORMAT "%100s"
#define CONSOLE_INPUT_BUFFER_SIZE 100
#define STRTOK_DIVIDER  " "

/////////////////////////////////////////////
/////////// Ошибки при исполнении /////////// 
/////////////////////////////////////////////

typedef enum {
    ONEGIN_OK = 1,
    ONEGIN_ERROR_INVALID_FLAG = 2,
    ONEGIN_ERROR_INVALID_FILE = 3,
    ONEGIN_ERROR_INTERNAL     = 4,
} onegin_error_t;

const char* onegin_errors[] = {
    [ONEGIN_OK]                 = NULL, // Нет комментария об ошибке
    [ONEGIN_ERROR_INVALID_FLAG] = "[onegin]: Был использован неверный флаг в приложении / либо неверно применён.",
    [ONEGIN_ERROR_INVALID_FILE] = "[onegin]: Возникла непредвиденная ошибка. Проверьте путь к файлу.",
    [ONEGIN_ERROR_INTERNAL]     = "[onegin]: Возникла внутренняя ошибка (Вероятно выделение памяти)."
};

/////////////////////////////////////////////
////////// Работа с аргументами ///////////// 
/////////////////////////////////////////////

typedef enum {
    // IN MAP ->
    FLAG_HELP,
    FLAG_QUIET,
    FLAG_INTERACTIVE,
    FLAG_IN,
    FLAG_OUT,
    // <-

    FLAG_FILE,
} app_flags_t;

const char* app_flags_map[] = {
    [FLAG_HELP]         = "--help",
    [FLAG_QUIET]        = "--quiet",
    [FLAG_INTERACTIVE]  = "--interactive",
    [FLAG_IN]           = "-i",
    [FLAG_OUT]          = "-o",
};

typedef struct {
    const char* path;
    int num; 
    const char** value;
} app_args_t;

/////////////////////////////////////////////
//////////// Объявление функций ///////////// 
/////////////////////////////////////////////

onegin_error_t onegin_interactive(void);
onegin_error_t onegin_quiet(app_args_t args);

int main(const int argc, const char* argv[]) {

    // Application state
    onegin_error_t status = 0;

    if (argc == 1) {
        /**
         * It must be interactive mode.
         */
        status = onegin_interactive();

        if (status != ONEGIN_OK) {
            perror(onegin_errors[status]);
            return EXIT_FAILURE;
        } else {
            return EXIT_SUCCESS;
        }
    } else {

        app_args_t args = {
            .num = argc - 1,
            .path = (*argv),
            .value = (argv + 1),
        };

        status = onegin_quiet(args);

        // ...
    }

    return EXIT_SUCCESS;
}

/**************************************************************************************************/
/**************************************************************************************************/

#define _COMPARE_GENERIC(op, arg1, arg2)\
    _Generic((arg1), \
        default:    ((arg1) op (arg2) ? (arg1) : (arg2)) \
    )

#define MIN(a, b)  _COMPARE_GENERIC(<, a, b)
#define MAX(a, b)  _COMPARE_GENERIC(>, a, b)

void onegin_qsort(void*, size_t, size_t, int(*compare_func)(const void*, const void*));
char** onegin_parse_text(char* text, size_t* lines);
void onegin_delete_blanks_text(char* text);

int strcmp_forward(const char* str1, const char* str2) {
    int len = MIN(strlen(str1), strlen(str2));
    int D = 0;
    for (int i = 0; i < len; ++i) {
        D += str1[i] - str2[i];
    }
    return D;
}

int strcmp_backward(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int D = 0;
    for (int i = len1, j = len2; i != 0 && j != 0; --i, --j) {
        D += str1[i] - str2[i];
    }
    return D;
}

int sort_strcmp_forward(const void* a, const void* b) {
    const char* str1 = *(const char**)(a);
    const char* str2 = *(const char**)(b);
    return strcmp_forward(str1, str2);
}

int sort_strcmp_backward(const void* a, const void* b) {
    const char* str1 = *(const char**)(a);
    const char* str2 = *(const char**)(b);
    return strcmp_backward(str1, str2);
}

/////////////////////////////////////////////
////////// Тихий режим приложения /////////// 
/////////////////////////////////////////////

const char* interactive_intro_msg = \
" #-----------------------------# \n"
" |                             | \n"
" [ ---- Приложение Онегин ---- ] \n"
" |                             | \n"
" #-----------------------------# \n";

const char* interactive_intro_input_msg
= "# Введите название входного файла -> ";
const char* interactive_intro_sort_msg
= "# Тип сортировки ? Прямая или обратная. [forward/backward] -> ";
const char* interactive_intro_output_msg
= "# Куда вывести результат? Введите Enter чтобы вывести в консоль, или же укажите путь к файлу-> ";
const char* interactive_intro_origin_msg 
= "# Желаете увидеть оригинальный текст? [y/n]";
const char* interactive_outro_msg 
= "# Нажмите любую клавишу....";

const char* sort_forward_str = "forward";
const char* sort_backward_str = "backward";

const char* origin_yes_str = "yes";
const char* origin_no_str = "no";


onegin_error_t onegin_interactive(void) {

    /////////////////////////////////////////////
    ////////// Запускается приложение /////////// 
    /////////////////////////////////////////////
    puts(interactive_intro_msg); // объединить?
    puts(interactive_intro_input_msg);

    char console_input_buffer[CONSOLE_INPUT_BUFFER_SIZE];
    memset(console_input_buffer, '\0', CONSOLE_INPUT_BUFFER_SIZE);

    scanf(SCANF_INPUT_BUFFER_FORMAT, console_input_buffer);
    
    if (strlen(console_input_buffer) < MIN_FILE_LEN) {
        return ONEGIN_ERROR_INVALID_FILE;
    }
        
    int file_descr = open(console_input_buffer, O_RDONLY);

    // Ошибка. Не удалось открыть файл. Неверный путь.
    if (file_descr < 0) {
        return ONEGIN_ERROR_INVALID_FILE;
    }
        

    struct stat file_info = (const struct stat){0};
    fstat(file_descr, &file_info);
    size_t file_size = file_info.st_size;

    // Ошибка. Файл вероятно пуст или повреждён.
    if (file_size == 0) {
        close(file_descr);
        return ONEGIN_ERROR_INVALID_FILE;
    }
        

    char* input_file_buffer = calloc(file_size + 1, sizeof(char));

    // Ошибка. Не удалось выделить память.
    if (input_file_buffer == NULL) {
        close(file_descr);
        return ONEGIN_ERROR_INTERNAL;
    }

    // Ошибка. Не удалось прочесть содержимое.
    if (read(file_descr, input_file_buffer, file_size) < 0) {
        free(input_file_buffer);
        close(file_descr);
        return ONEGIN_ERROR_INTERNAL;   
    }

    // Нуль-терминатор
    input_file_buffer[file_size] = '\0';

    char* origin_buffer = calloc(file_size + 1, sizeof(char));
    memcpy(origin_buffer, input_file_buffer, file_size + 1);


    
    close(file_descr);

    onegin_delete_blanks_text(input_file_buffer);

    size_t lines = 0;
    char** parsed_lines = onegin_parse_text(input_file_buffer, &lines);

    // Ошибка. Не удалось разбить файл на строки.
    if (parsed_lines == NULL) {
        free(input_file_buffer);
        return ONEGIN_ERROR_INTERNAL;
    }
    
    for (size_t i = 0; i < lines; ++i) {
        printf("[%lu]: %s\n", i+1, parsed_lines[i]);
    }

    /////////////////////////////////////////////
    /////////// Выбор типа сортировки /////////// 
    /////////////////////////////////////////////
    puts(interactive_intro_sort_msg);

    memset(console_input_buffer, '\0', CONSOLE_INPUT_BUFFER_SIZE);
    scanf(SCANF_INPUT_BUFFER_FORMAT, console_input_buffer);

    // Выбирает самое похожее. Возможно кринж.
    if (strcmp(console_input_buffer, sort_forward_str) < strcmp(console_input_buffer, sort_backward_str)) {
        onegin_qsort(parsed_lines, sizeof(char*), lines, sort_strcmp_forward);
    } else {
        onegin_qsort(parsed_lines, sizeof(char*), lines, sort_strcmp_backward);
    }

    /////////////////////////////////////////////
    /////////// Выбор выходного файла /////////// 
    /////////////////////////////////////////////
    puts(interactive_intro_output_msg);

    memset(console_input_buffer, '\0', CONSOLE_INPUT_BUFFER_SIZE);
    // scanf(SCANF_INPUT_BUFFER_FORMAT, console_input_buffer);
    getchar();
    if (fgets(console_input_buffer, CONSOLE_INPUT_BUFFER_SIZE, stdin) != NULL) {
        if (console_input_buffer[0] == '\n') {
            for (size_t i = 0; i < lines; ++i) {
                printf("[%lu]: %s\n", i+1, parsed_lines[i]);
            }
        } else {
            size_t len = strlen(console_input_buffer);
            if (console_input_buffer[len - 1] == '\n') {
                console_input_buffer[len - 1] = '\0';
            }

            if (strlen(console_input_buffer) < MIN_FILE_LEN) {
                return ONEGIN_ERROR_INVALID_FILE;
            }

            FILE* output_file_descr = fopen(console_input_buffer, "w+");

            if (output_file_descr == NULL) {
                free(origin_buffer);
                free(input_file_buffer);
                return ONEGIN_ERROR_INVALID_FILE;
            }
                

            for (size_t i = 0; i < lines; ++i) {
                fputs(parsed_lines[i], output_file_descr);
                fputc('\n', output_file_descr);
            }

            fclose(output_file_descr);
        }
    }
    

    /////////////////////////////////////////////
    ////////////// Вывод оригинала ////////////// 
    /////////////////////////////////////////////
    puts(interactive_intro_origin_msg);

    memset(console_input_buffer, '\0', CONSOLE_INPUT_BUFFER_SIZE);
    scanf(SCANF_INPUT_BUFFER_FORMAT, console_input_buffer);
    
    // Выбирает самое похожее. Возможно кринж.
    if (strcmp(console_input_buffer, origin_yes_str) < strcmp(console_input_buffer, origin_no_str)) {
        printf("\t Исходный текст файла:\n\n%s", origin_buffer);
    }

    // Освобождаем область памяти с исходным файлом
    free(input_file_buffer);
    free(origin_buffer);

    /////////////////////////////////////////////
    //////// Завершение работы программы //////// 
    /////////////////////////////////////////////
    puts(interactive_outro_msg);
    getchar();
    getchar();
}

/////////////////////////////////////////////
///////// Обычный режим приложения ////////// 
/////////////////////////////////////////////

onegin_error_t onegin_quiet(app_args_t args) {
    // не нужен )
}

/////////////////////////////////////////////
/////////// "Приватные" функции ///////////// 
/////////////////////////////////////////////

void _onegin_qsort_swap(void* data1, void* data2, size_t size) {

    uint8_t* casted_data1 = (uint8_t*)(data1);
    uint8_t* casted_data2 = (uint8_t*)(data2);
    uint8_t temp;

    for (size_t i = 0; i < size; ++i) {
        temp = casted_data1[i];
        casted_data1[i] = casted_data2[i];
        casted_data2[i] = temp;
    }
}

void _onegin_qsort_rec(
    void* base, 
    size_t size_of_element,
    size_t left,
    size_t right, 
    int(*compare_func)(const void*, const void*)) {

    if (left >= right) return;

    size_t i = left, j = right;
    void* pivot = (char*)base + ((left + right) / 2) * size_of_element;

    while (i <= j) {
        while (compare_func((char*)base + i * size_of_element, pivot) < 0) {
            i++;
        }
        while (compare_func((char*)base + j * size_of_element, pivot) > 0) {
            j--;
        }

        if (i <= j) {
            _onegin_qsort_swap((char*)base + i * size_of_element, (char*)base + j * size_of_element, size_of_element);
            i++;
            if (j > 0) j--;
        }
    }

    if (left < j) _onegin_qsort_rec(base, size_of_element, left, j, compare_func);
    if (i < right) _onegin_qsort_rec(base, size_of_element, i, right, compare_func);
}


void onegin_qsort (
        void* base, 
        size_t size_of_element, 
        size_t num_of_elements, 
        int(*compare_func)(const void*, const void*)
    ){

    if (base != NULL)
        _onegin_qsort_rec(base, size_of_element, 0, num_of_elements - 1, compare_func);
}

void onegin_delete_blanks_text(char* text) {
    if (text == NULL) {
        return;
    }

    char *write_ptr = text;
    bool is_newline = false;

    while ((*text) != '\0') {
        if ((*text) == '\n') {
            if (!is_newline) {
                *(write_ptr++) = (*text);
                is_newline = true;
            }
        } else {
            *(write_ptr++) = (*text);
            is_newline = false;
        }
        text++;
    }

    *write_ptr = '\0';
}

char** onegin_parse_text(char* text, size_t* lines) {
    if (text == NULL) {
        return NULL;
    }

    char* text_ptr = text;
    size_t _lines = 0;
    do {
        text_ptr = strchr(text_ptr, '\n');
        if (text_ptr == NULL) {
            break;
        } 
        (*text_ptr) = '\0';
        text_ptr++;
        _lines++;
    } while(1);

    text_ptr = text;
    char** text_lines = calloc(_lines, sizeof(char*));

    for (size_t i = 0; i < _lines; ++i) {
        text_lines[i] = text;
        text = strchr(text, '\0') + 1;
    }

    (*lines) = _lines;

    return text_lines;
}

#else
#   error "Приложение создано только для Linux."
#endif