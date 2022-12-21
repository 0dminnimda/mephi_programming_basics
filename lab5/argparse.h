#include <stdlib.h>

#include "sort_type.h"
#include "voters.h"

typedef struct Options {
    char *input_file;
    char *output_file;

    size_t array_length;
    size_t n_iterations;

    int reverse;
    field_t field;
    sort_t sort;

    int verbose;
} Options;

Options default_options();
void print_options(Options options);
int parse(int argc, char *argv[], Options *options);
