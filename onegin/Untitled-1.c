#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define _COMPARE_GENERIC(op, arg1, arg2)\
    _Generic((arg1), \
        default:    ((arg1) op (arg2) ? (arg1) : (arg2)) \
    )

#define MIN(a, b)  _COMPARE_GENERIC(<, a, b)
#define MAX(a, b)  _COMPARE_GENERIC(>, a, b)

int my_strlen(const char* str1) {
    int len = 0;
    while ((*str1) != '\0') {
        len++; str1++;
    }
    return len;
}

int my_strcmp(const char* str1, const char* str2) {
    int len = MIN(my_strlen(str1), my_strlen(str2));
    int D = 0;
    for (int i = 0; i < len; ++i) {
        D += str1[i] - str2[i];
    }
    return D;
}

int sort_str_cmp(const void* a, const void* b) {
    const char* str1 = *(const char**)(a);
    const char* str2 = *(const char**)(b);
    printf("[1]: %s\n[2]: %s\n\n", str1, str2);
    return my_strcmp(str1, str2);
}

void _lqsort(int* base, size_t left, size_t right, int(*compare_func)(int, int)) {

    size_t i = left, j = right;
    int pivot = base[(left + right) / 2];

    if (i <= j) {
        while (compare_func(base[i], pivot) < 0)
            i++;
        while (compare_func(base[j], pivot) > 0)
            j--;

        if (i <= j) {
            int temp = base[i];
            base[i] = base[j];
            base[j] = temp;
            i++;
            j--;
        }
    }
    
    if (j > left)
        _lqsort(base, left, j, compare_func);
        
    if (i < right)
        _lqsort(base, i, right, compare_func);

}

void lqsort(int* base, int num_of_elements, int(*compare_func)(int, int)) {
    _lqsort(base, 0, num_of_elements, compare_func);
}

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

    size_t i = left, j = right;
    void* pivot = (char*)(base) + (((left + right) / 2) * size_of_element);
    void* temp = calloc(1, size_of_element);

    if (i <= j) {
        
        
        while (compare_func(((char*)(base) + (i * size_of_element)), pivot) < 0)
            i++;
        while (compare_func(((char*)(base) + (j * size_of_element)), pivot) > 0)
            j--;

        if (i <= j) {
            memcpy(temp, (char*)(base) + (i * size_of_element), size_of_element);
            memcpy(((char*)(base) + (i * size_of_element)), ((char*)(base) + (j * size_of_element)), size_of_element);
            memcpy(((char*)(base) + (j * size_of_element)), temp, size_of_element);
            i++;
            j--;
        }
    }

    free(temp);

    if (left < j)
        _onegin_qsort_rec(base, size_of_element, left, j, compare_func);
        
    if (right > i)
        _onegin_qsort_rec(base, size_of_element, i, right, compare_func);

}


void onegin_qsort(
    void* base, 
    size_t size_of_element, 
    size_t num_of_elements, 
    int(*compare_func)(const void*, const void*)){
    _onegin_qsort_rec(base, size_of_element, 0, num_of_elements - 1, compare_func);
}

int main(void) {
    
    char* str[] = {
        "aaa",
        "aab",
        "abb",
        "bbb",
        "a"
    };
    const size_t num_of_el = sizeof(str) / sizeof(str[0]);
    onegin_qsort(str, sizeof(char*), num_of_el, sort_str_cmp);
    
    for (size_t i = 0; i < num_of_el; ++i){
        printf_s("[%d]: %s\n", i, str[i]);
    }
    return 0;
}