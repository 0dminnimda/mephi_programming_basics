#include "commands.h"

#include <stdio.h>
#include <string.h>

int init_command(char *str, Vector vec) {
    reset_length(vec);
    float value;
    int offset;
    char *ptr = str;
    while (sscanf_s(ptr, "%f%n", &value, &offset) == 1) {
        ptr += offset;
        if (push_back(vec, value)) {
            printf("Could not push_back %f into Vector\n", value);
            return 0;
        }
    }
    return 0;
}

int insert_command(char *str, Vector vec) { return 0; }

int remove_at_command(char *str, Vector vec) { return 0; }

int process_data_command(char *str, Vector vec) { return 0; }

int print_command(char *str, Vector vec) {
    for (size_t i = 0; i < get_length(vec); i++)
        printf("%f ", get_item(vec, i));
    if (get_length(vec)) printf("\n");
    return 0;
}
