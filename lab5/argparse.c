#include "argparse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define error(...) (fprintf(stderr, __VA_ARGS__), 1)
#define help() error(usage, argv[0])
#define big_help(...) (error(__VA_ARGS__), help())
#define smol_help(...) (error(__VA_ARGS__), error("Run %s -h for more informaiton\n", argv[0]))

void print_getopt_state(int opt) {
    printf(
        "optind: %d\t"
        "opterr: %d\t"
        "optopt: %c (%d)\t"
        "opt: %c (%d)\t"
        "\n",
        optind, opterr, optopt, optopt, opt, (char)opt);
}

Options default_options() {
    return (Options){.input_file = NULL,
                     .output_file = NULL,
                     .array_length = 0,
                     .array_count = 0,
                     .reserve = 0,
                     .field_offset = 0,
                     .sort = QuickSort};
}

void print_options(Options options) {
    if (options.input_file) printf("  input file: '%s'\n", options.input_file);
    if (options.output_file) printf("  output file: '%s'\n", options.output_file);

#if !(PROGRAM_ID == 1)
    printf("  array length: %zu\n", options.array_length);
    printf("  array count: %zu\n", options.array_count);
#endif  // PROGRAM_ID

    printf("  reserved order: %s\n", options.reserve? "Yes" : "No");
    printf("  field_offset: %zu\n", options.field_offset);
    printf("  sort: %s\n", sort2str(options.sort));
}

int parse(int argc, char *argv[], Options *options) {
    char usage[] =
        "Usage: %s [options] "
#if PROGRAM_ID == 1
        "<input_file> <output_file>\n"
#else
        "<array_length> <array_count>\n\
\n\
  array_length   Number of elements in the generated array.\n\
  array_count    Number of arrays to generate.\n"
#endif  // PROGRAM_ID
        "\nOptions:\n\
  -h             Show help.\n\
  -r             Reverse the sorting direction.\n\
  -n field       Field which will be used as a sorting key.\n\
  -s sort        What sorting algorithm to use (Q by default).\n\
                   B - BubbleSort\n\
                   D - DoubleSelectionSort\n\
                   Q - QuickSort\n\
\n ";

    int opt;
    *options = default_options();

    while ((opt = getopt(argc, argv, ":hrn:s:")) != -1) {
        print_getopt_state(opt);

        switch (opt) {
            case 'h':
                return help();
                break;
            case 'r':
                options->reserve = 1;
                break;
            case 'n':
                break;
            case 's':
                options->sort = char2sort(*optarg);
                if (options->sort >= SortCount || strlen(optarg) != 1)
                    return smol_help("Invalid sort '%s'\n\n", optarg);
                break;
            case ':':
                return big_help("Option '%c' requires a value\n\n", optopt);
            case '?':
                return big_help("Unknown option '%c'\n\n", optopt);
        }
    }

    if (argc == 1) return help();

    if (optind + 1 >= argc)
        return big_help("Expected 2 positional arguments, found %d\n\n",
                    argc - optind);

#if PROGRAM_ID == 1
    options->input_file = argv[optind];
    options->output_file = argv[optind + 1];
#else
    if (strspn(argv[optind], "0123456789") != strlen(argv[optind]))
        return smol_help("Invalid array_length '%s', must be an integer\n\n", argv[optind]);
    options->array_length = atoi(argv[optind]);

    if (strspn(argv[optind + 1], "0123456789") != strlen(argv[optind + 1]))
        return smol_help("Invalid array_count '%s', must be an integer\n\n", argv[optind + 1]);
    options->array_count = atoi(argv[optind + 1]);
#endif  // PROGRAM_ID

    printf("Using these options:\n");
    print_options(*options);

    return 0;
}
