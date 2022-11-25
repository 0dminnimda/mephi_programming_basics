#include "my_string.h"

size_t strcspn(const char *str1, const char *str2) {
    size_t index = -1;
    while (str1[++index] != '\0') {
        size_t i = -1;
        while (str2[++i] != '\0') {
            if (str1[index] == str2[i]) return index;
        }
    }
    return index;
}
