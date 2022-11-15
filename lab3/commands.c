#include "commands.h"

#include <stdio.h>
#include <string.h>

int init_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Initializes the data\n");
        printf("%sUse: init [item ...]\n", str);
        printf("%sExample: init 3.1415 2.7182 .42 0\n", str);
        return 0;
    }

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
            destroy_rational(value);
            return 0;
        }
    }
    if (resize(vec, get_length(vec))) {
        clear_vector(vec);
        printf("Could not resize the Vector to %zu\n", get_length(vec));
        destroy_rational(value);
        return 0;
    }
    destroy_rational(value);
    return 0;
}

int resize_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Resizes the data\n");
        printf("%sUse: resize capacity\n", str);
        printf("%sExample: resize 10\n", str);
        return 0;
    }

    size_t capacity = 0;
    if (sscanf(str, "%zu", &capacity) != 1) {
        printf("Incorrect input, expected capacity (size_t)\n");
        return 0;
    }

    if (resize(vec, capacity)) {
        printf("Could not resize the Vector to %zu\n", capacity);
        return 0;
    }
    return 0;
}

int insert_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Inserts the given value at the given index\n");
        printf("%sUse: insert index value\n", str);
        printf("%sExample: insert 2 34.35\n", str);
        return 0;
    }

    int offset;
    size_t index = 0;
    if (sscanf(str, "%zu%n", &index, &offset) != 1) {
        printf("Incorrect input, expected index (size_t)\n");
        return 0;
    }

    Rational value;
    if (sscan_rational(str + offset, &value, &offset)) {
        printf("Incorrect input, expected value (Rational)\n");
        destroy_rational(value);
        return 0;
    }

    if (index > get_length(vec)) {
        printf(
            "Invalid index (%zu), expected to be less than or equal to length "
            "(%zu)\n",
            index, get_length(vec));
        destroy_rational(value);
        return 0;
    }

    if (index == get_capacity(vec)) {
        destroy_rational(value);
        return 0;
    }

    if (get_capacity(vec) != get_length(vec)) {
        if (push_back(vec, NULL)) {
            printf("Could not push_back into Vector\n");
            destroy_rational(value);
            return 0;
        }
    } else {
        destroy_rational(get_item(vec, get_length(vec) - 1));
    }

    for (size_t i = get_length(vec) - 1; i > index; i--)
        set_item(vec, i, get_item(vec, i - 1));

    set_item(vec, index, value);
    return 0;
}

int remove_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Removes an item at the given index\n");
        printf("%sUse: remove index\n", str);
        printf("%sExample: remove 1\n", str);
        return 0;
    }

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

    Rational removed_item = get_item(vec, index);
    for (size_t i = index; i < get_length(vec) - 1; i++)
        set_item(vec, i, get_item(vec, i + 1));

    set_item(vec, get_length(vec) - 1, removed_item);
    pop_back(vec);
    return 0;
}

int process_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Prints and removes items which fractional part is bigger than decimal\n");
        printf("%sUse: process\n", str);
        return 0;
    }

    Vector vec_trash;
    if (create(&vec_trash, get_capacity(vec))) {
        printf("Could not create a Vector\n");
        return 0;
    }

    Vector vec_rest;
    if (create(&vec_rest, get_capacity(vec))) {
        printf("Could not create a Vector\n");
        return 0;
    }

    for (size_t i = 0; i < get_length(vec); i++) {
        Rational item = get_item(vec, i);
        if (get_fractional(item) > get_decimal(item))
            push_back(vec_trash, item);
        else
            push_back(vec_rest, item);
    }

    printf("Removed ");
    print_command(" --less", vec_trash, 0);
    destroy_vector(vec_trash);

    swap_vectors(vec, vec_rest);
    destroy_reference(vec_rest);

    return 0;
}

int print_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Prints the state of the data\n");
        printf("%sUse: print [--less]\n", str);
        printf("%sExample: print\n", str);
        return 0;
    }

    printf("[");
    if (get_length(vec)) print_rational(get_item(vec, 0));
    for (size_t i = 1; i < get_length(vec); i++) {
        printf(" ");
        print_rational(get_item(vec, i));
    }
    printf("]");

    int offset = 0;
    sscanf(str, " --less%n", &offset);
    if (offset == 0 && get_capacity(vec) - get_length(vec)) {
        printf(" + (%zu) empty items", get_capacity(vec) - get_length(vec));
    }

    printf("\n");
    return 0;
}
