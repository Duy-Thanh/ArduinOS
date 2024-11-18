#include "string.h"

s8 str_compare(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

u16 str_length(const char* str) {
    u16 len = 0;
    while (*str++) {
        len++;
    }
    return len;
}

void str_copy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}