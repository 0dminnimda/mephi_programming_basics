#include "commands.h"

#include <stdio.h>
#include <string.h>

int scan_one(char **str_ptr, char *format, void *data) {
    int offset = 0;
    strcat_s(format, 2, "%n");
    int result = sscanf_s(*str_ptr, format, data, &offset);
    *str_ptr += offset;
    return result;
}

int init_command(char *str, Vector vec) {
    reset_length(vec);
    float value;
    int offset;
    char *ptr = str;
    // scan_one(&str, "%f", &value)
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

int decimal_digits(float number) {
    return 1 + (number >= 0.1000000000000000000) +
           (number >= 00.100000000000000000) +
           (number >= 000.10000000000000000) +
           (number >= 0000.1000000000000000) +
           (number >= 00000.100000000000000) +
           (number >= 000000.10000000000000) +
           (number >= 0000000.1000000000000) +
           (number >= 00000000.100000000000) +
           (number >= 000000000.10000000000) +
           (number >= 0000000000.1000000000) +
           (number >= 00000000000.100000000) +
           (number >= 000000000000.10000000) +
           (number >= 0000000000000.1000000) +
           (number >= 00000000000000.100000) +
           (number >= 000000000000000.10000) +
           (number >= 0000000000000000.1000) +
           (number >= 00000000000000000.100) +
           (number >= 000000000000000000.10) +
           (number >= 0000000000000000000.1);
}

void as_ratio(float rational) {  //}, long *integer, long *power) {
    unsigned long long integer = rational;
    unsigned long long power = 1;
    long double long_rational = rational;
    for (int i = 0; i < 20; i++) {
        long double im = ((long double)integer / power);
        if (rational == (float)im) break;
        long double diff = long_rational - im;
        unsigned long long digit = diff * power;
        // printf("%Lf %lf %Lf %Lf %lld %lld\n", diff, rational - (float)im,
        // diff * power, im, integer, digit);
        integer += digit;
        integer *= 10;
        power *= 10;
    }
    printf("%lld %lld\n", integer, power);
}

void count_digits(float rational) {
    unsigned long long integer = rational;
    unsigned int whole = 0;
    while (integer) {
        whole++;
        printf("%lld %d\n", integer, whole);
        integer /= 10;
    }
    if (whole < 1)
        whole = 1;

    unsigned int decimal = 0;
    unsigned long long power = 1;
    integer = rational;
    long double long_rational = rational;
    for (int i = 0; i < 20; i++) {
        long double im = ((long double)integer / power);
        if (rational == (float)im) break;
        integer += (long_rational - im) * power;
        integer *= 10;
        power *= 10;
        decimal++;
        printf("%d", integer);
    }
    // while ()
    printf("%lld %lld\n", integer, power);

    // float power = 10;
    // float prev = rational - 1;
    // while (prev != rational) {
    //     prev = rational;
    //     rational -= (float)floor(rational * power) / power;
    //     decimal++;
    //     power *= 10;
    //     printf("%lf %d %lf %d\n", rational, decimal, (float)floor(rational * power) / power, ((float)floor(rational * power) / power) == 0);
    // }

    printf("%d %d", whole, decimal);
}

int process_data_command(char *str, Vector vec) {
    float value = 0;
    if (sscanf_s(str, "%f", &value) != 1) {
        printf("Incorrect input, expected value (float)\n");
        return 0;
    }

    as_ratio(value);
    count_digits(value);
    printf("\n");

    float gg = 1.33445566778899f;
    long g = (long)11223344556677.8899f;
    printf("%lf ", 1122.33445566778899f);
    printf("%lf ", 1122.33445566778899f - 1122);
    printf("%lf ", (1122.33445566778899f - 1122) * 10 - 3);
    printf("%lf ", ((1122.33445566778899f - 1122) * 10 - 3) * 10 - 3);
    printf("%lf ",
           (((1122.33445566778899f - 1122) * 10 - 3) * 10 - 3) * 10 - 4);
    printf("%lf ",
           ((((1122.33445566778899f - 1122) * 10 - 3) * 10 - 3) * 10 - 4) * 10 -
               4);
    printf(
        "%lf ",
        (((((1122.33445566778899f - 1122) * 10 - 3) * 10 - 3) * 10 - 4) * 10 -
         4) * 10 -
            5);

    // printf("9 %d\n", (float)123.123456789123456789 ==
    // (float)123.12345678912345678); printf("8 %d\n",
    // (float)123.12345678912345678 == (float)123.1234567891234567); printf("7
    // %d\n", (float)123.1234567891234567 == (float)123.123456789123458);
    // printf("6 %d\n", (float)123.123456789123456 ==
    // (float)123.12345678912345); printf("5 %d\n", (float)123.12345678912345 ==
    // (float)123.1234567891234); printf("4 %d\n", (float)123.1234567891234 ==
    // (float)123.123456789123); printf("3 %d\n", (float)123.123456789123 ==
    // (float)123.12345678912); printf("2 %d\n", (float)123.12345678912 ==
    // (float)123.1234567891); printf("1 %d\n", (float)123.1234567891 ==
    // (float)123.123456789); printf("9 %d\n", (float)123.123456789 ==
    // (float)123.12345678); printf("8 %d\n", (float)123.12345678 ==
    // (float)123.1234567); printf("7 %d\n", (float)123.1234567 ==
    // (float)123.123456); printf("6 %d\n", (float)123.123456 ==
    // (float)123.12345); printf("5 %d\n", (float)123.12345 == (float)123.1234);
    // printf("4 %d\n", (float)123.1234 == (float)123.123);
    // printf("3 %d\n", (float)123.123 == (float)123.12);
    // printf("2 %d\n", (float)123.12 == (float)123.1);

    // printf("\n");

    // printf("9 %d\n", (float)923.123456789123456789 ==
    // (float)923.12345678912345678); printf("8 %d\n",
    // (float)923.12345678912345678 == (float)923.1234567891234567); printf("7
    // %d\n", (float)923.1234567891234567 == (float)923.123456789123458);
    // printf("6 %d\n", (float)923.123456789123456 ==
    // (float)923.12345678912345); printf("5 %d\n", (float)923.12345678912345 ==
    // (float)923.1234567891234); printf("4 %d\n", (float)923.1234567891234 ==
    // (float)923.123456789123); printf("3 %d\n", (float)923.123456789123 ==
    // (float)923.12345678912); printf("2 %d\n", (float)923.12345678912 ==
    // (float)923.1234567891); printf("1 %d\n", (float)923.1234567891 ==
    // (float)923.123456789); printf("9 %d\n", (float)923.123456789 ==
    // (float)923.12345678); printf("8 %d\n", (float)923.12345678 ==
    // (float)923.1234567); printf("7 %d\n", (float)923.1234567 ==
    // (float)923.123456); printf("6 %d\n", (float)923.123456 ==
    // (float)923.12345); printf("5 %d\n", (float)923.12345 == (float)923.1234);
    // printf("4 %d\n", (float)923.1234 == (float)923.123);
    // printf("3 %d\n", (float)923.123 == (float)923.12);
    // printf("2 %d\n", (float)923.12 == (float)923.1);

    printf("E %E\n", value);
    // printf("u %u\n", value);
    // printf("'f %'f\n", value);
    // printf("' f '%f\n", value);
    // printf("f' %f'\n", value);
    printf("%f\n", (value / 0.000000000001));

    int biggest = 0;
    for (int i = 1, div = 10; i < 15; i++, div *= 10) {
        float num = (float)1 / div;
        // printf("%lf ", num);
        if (value <= num) biggest = i;
        // printf("%");
    }
    printf("%d \n", biggest);
    return 0;
}

int print_command(char *str, Vector vec) {
    for (size_t i = 0; i < get_length(vec); i++) {
        printf("%f ", get_item(vec, i));
        printf("%.15lf ", (double)get_item(vec, i));
    }
    if (get_length(vec)) printf("\n");
    return 0;
}
