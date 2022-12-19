#include <stdlib.h>

#include "sort_type.h"
#include "voters.h"

typedef struct Options {
    char *input_file;
    char *output_file;

    size_t array_length;
    size_t array_count;

    int reverse;
    voter_field field;
    sort_id sort;
} Options;

Options default_options();
void print_options(Options options);
int parse(int argc, char *argv[], Options *options);
