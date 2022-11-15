#include "commands.h"

#include <stdio.h>
#include <string.h>

int init_command(char *str, Vector vec) {
    clear_vector(vec);
    int offset = 0;
    Rational value;
    while (!sscan_rational(str, &value, &offset)) {
        str += offset;
        if (push_back(vec, value)) {
            clear_vector(vec);
            printf("Could not push_back ");
            print_rational(value);
            printf(" into Vector\n");
            return 0;
        }
    }
    if (resize(vec, get_length(vec))) {
        clear_vector(vec);
        printf("Could not resize the Vector\n");
        return 0;
    }
    return 0;
}

int insert_command(char *str, Vector vec) {
    int offset;
    size_t index = 0;
    if (sscanf(str, "%zu%n", &index, &offset) != 1) {
        printf("Incorrect input, expected index (size_t)\n");
        return 0;
    }

    Rational value;
    if (sscan_rational(str + offset, &value, &offset)) {
        printf("Incorrect input, expected value (Rational)\n");
        return 0;
    }

    if (index > get_length(vec)) {
        printf(
            "Invalid index (%zu), expected to be less than or equal to length "
            "(%zu)\n",
            index, get_length(vec));
        return 0;
    }

    if (get_capacity(vec) != get_length(vec))
        if (push_back(vec, get_item(vec, get_length(vec) - 1))) {
            printf("Could not push_back into Vector\n");
            return 0;
        }

    for (size_t i = get_length(vec); i > index; i--)
        set_item(vec, i, get_item(vec, i - 1));

    set_item(vec, index, value);
    return 0;
}

int remove_command(char *str, Vector vec) {
    size_t index = 0;
    if (sscanf(str, "%zu", &index) != 1) {
        printf("Incorrect input, expected index (size_t)\n");
        return 0;
    }

    if (index >= get_length(vec)) {
        printf("Invalid index (%zu), expected to be less than length (%zu)\n",
               index, get_length(vec));
        return 0;
    }

    for (size_t i = index; i < get_length(vec) - 1; i++)
        set_item(vec, i, get_item(vec, i + 1));

    pop_back(vec);
    return 0;
}

int process_command(char *str, Vector vec) {
    Vector vec2;
    if (create(&vec2, get_capacity(vec))) {
        printf("Could not create a Vector\n");
        return 0;
    }

    size_t length = get_length(vec);
    reset_length(vec);

    for (size_t i = 0; i < length; i++) {
        Rational item = get_item(vec, i);
        if (get_fractional(item) > get_decimal(item))
            push_back(vec2, item);
        else
            push_back(vec, item);
    }

    print_command(str, vec2);
    destroy_vector(vec2);

    return 0;
}

int print_command(char *str, Vector vec) {
    printf("[");
    if (get_length(vec)) print_rational(get_item(vec, 0));
    for (size_t i = 1; i < get_length(vec); i++) {
        printf(" ");
        print_rational(get_item(vec, i));
    }
    printf("]\n");
    return 0;
}
