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
            reset_length(vec);
            printf("Could not push_back %f into Vector\n", value);
            return 0;
        }
    }
    return 0;
}

int insert_command(char *str, Vector vec) {
    size_t index = 0;
    float value = 0;
    if (sscanf_s(str, "%zu%f", &index, &value) != 2) {
        printf("Incorrect input, expected index (size_t) and value (float)\n");
        return 0;
    }

    if (index > get_length(vec)) {
        printf(
            "Invalid index (%zu), expected to be less than or equal to length "
            "(%zu)\n",
            index, get_length(vec));
        return 0;
    }

    if (push_back(vec, .0)) {
        printf("Could not push_back %f into Vector\n", .0);
        return 0;
    }

    for (size_t i = get_length(vec); i > index; i--)
        set_item(vec, i, get_item(vec, i - 1));

    set_item(vec, index, value);
    return 0;
}

int remove_command(char *str, Vector vec) {
    size_t index = 0;
    if (sscanf_s(str, "%zu", &index) != 1) {
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

int process_data_command(char *str, Vector vec) { return 0; }
void as_ratio(float rational) {//}, long *integer, long *power) {
    unsigned long long integer = rational;
    unsigned long long power = 1;
    long double long_rational = rational;
    for (int i = 0; i < 20; i++) {
        long double im = ((long double)integer / power);
        if (rational == (float)im)
            break;
        long double diff = long_rational - im;
        unsigned long long digit = diff * power;
        // printf("%Lf %lf %Lf %Lf %lld %lld\n", diff, rational - (float)im, diff * power, im, integer, digit);
        integer += digit;
        integer *= 10;
        power *= 10;
    }
    printf("%lld %lld", integer, power);
}


int print_command(char *str, Vector vec) {
    for (size_t i = 0; i < get_length(vec); i++)
        printf("%f ", get_item(vec, i));
    if (get_length(vec)) printf("\n");
    return 0;
}
