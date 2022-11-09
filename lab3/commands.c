#include "commands.h"

#include <stdio.h>
#include <string.h>

int init_command(char *str, Vector vec) {
    size_t str_len = strlen(str);

    int offset;
    char *ptr = str;

    size_t len;
    printf("%p %p %d | ", str, ptr, str_len);
    if (sscanf_s(ptr, "%zu%n", &len, &offset, str_len) != 1) {
        printf("Invalid input, expected an integer\n");
        return 0;
    }
    ptr += offset;
    str_len -= offset;

    if (reserve(vec, len)) {
        printf("Could not reserve %zu items for Vector\n", len);
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        float value;
        printf("%p %p %d | ", str, ptr, str_len);
        if (sscanf_s(ptr, "%f%n", &value, &offset, str_len) != 1) {
            printf("Invalid input, expected an integer\n");
            return 0;
        }
        ptr += offset;
        str_len -= offset;
        set_item(vec, i, value);
        // if (push_back(vec, value)) {
        //     printf("Could not push_back %f into Vector\n", value);
        //     return 0;
        // }
    }
    printf("%p %p %d | ", str, ptr, str_len);

    // float value;
    // int offset;
    // char *ptr = str;
    // while (printf(">'%s'< ", ptr), sscanf(ptr, "%f%n", &value, &offset) == 1) {
    //     printf("%f ", value);
    //     if (push_back(vec, value)) {
    //         printf("Could not push_back %f into Vector\n", value);
    //         return 0;
    //     }
    //     ptr += offset;
    // }

    printf("end\n");
    return 0;
}

int insert_command(char *str, Vector vec) { return 0; }

int remove_at_command(char *str, Vector vec) { return 0; }

int process_data_command(char *str, Vector vec) { return 0; }

int print_command(char *str, Vector vec) {
    for (size_t i = 0; i < get_length(vec); i++)
        printf("%f ", get_item(vec, i));
    printf("\n");
    return 0;
}
