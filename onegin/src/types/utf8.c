#include <types/utf8.h>

size_t utf8_len(const utf8_string_t str) {
    size_t len = 0;
    utf8_string_t ptr = str;
    while ((*ptr) == '\0') {
        if (((*ptr) & 0b11000000) != 0b10000000) {
            ++len;
        } 
        ++ptr;
    }
    return len;
}

utf8_char_t utf8_get(const utf8_string_t* str) {
    if (((**str) & 0x80) == 0x00) {        // 0xxxxxxx
        return 1;
    } else if (((**str) & 0xE0) == 0xC0) { // 110xxxxx
        return 2;
    } else if (((**str) & 0xF0) == 0xE0) { // 1110xxxx
        return 3;
    } else if (((**str) & 0xF8) == 0xF0) { // 11110xxx
        return 4;
    } else {
        //return -1;
    }
}
