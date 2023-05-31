#include "argparse.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define error(...) (fprintf(stderr, __VA_ARGS__), 1)
#define help() error(usage, argv[0])
#define big_help(...) (error(__VA_ARGS__), help())
#define smol_help(...) \
    (error(__VA_ARGS__), error("Run %s -h for more informaiton\n", argv[0]))

Options default_options() {
    return (Options){.input_file = NULL,
                     .output_file = NULL,
                     .array_length = 0,
                     .n_iterations = 1,
                     .reverse = 0,
                     .field = voter_name,
                     .sort = QuickSort,
                     .verbose = 0,
                     .warn = 1};
}

void print_options(Options options) {
    if (options.input_file) printf("  input file: '%s'\n", options.input_file);
    if (options.output_file)
        printf("  output file: '%s'\n", options.output_file);

#if !(PROGRAM_ID == 1)
    printf("  array length: %zu\n", options.array_length);
    printf("  n_iterations: %zu\n", options.n_iterations);
#endif  // PROGRAM_ID

    printf("  reversed order: %s\n", options.reverse ? "Yes" : "No");
    printf("  field: %s\n", field2str(options.field));
    printf("  sort: %s\n", sort2str(options.sort));
}

int parse(int argc, char *argv[], Options *options) {
    char usage[] =
        "Usage: %s [options] "
#if PROGRAM_ID == 1
        "<input_file> <output_file>\n"
#else
        "<array_length> <n_iterations>\n\
\n\
  array_length   Number of elements in the generated array.\n\
  n_iterations   Number of iterations for generating an array and measuring it sorting time.\n"
#endif  // PROGRAM_ID
        "\nOptions:\n\
  -h             Show help.\n\
  -v             Give more output, make it verbose.\n\
  -w             Don't show warnings.\n\
  -r             Reverse the sorting direction.\n\
  -f field       Field which will be used as a sorting key (name by default).\n\
                     name    - Full name of the voter\n\
                     station - Identifier of the polling station\n\
                     age     - Age of the voter\n\
  -s sort        What sorting algorithm to use (Q by default).\n\
                     B       - BubbleSort\n\
                     D       - DoubleSelectionSort\n\
                     Q       - QuickSort\n\
\n";

    int opt;
    *options = default_options();

    while ((opt = getopt(argc, argv, ":hrvwf:s:")) != -1) {
        switch (opt) {
            case 'h':
                return help();
            case 'r':
                options->reverse = 1;
                break;
            case 'v':
                options->verbose = 1;
                break;
            case 'w':
                options->warn = 0;
                break;
            case 'f':
                options->field = str2field(optarg);
                if (options->field >= voter_field_count)
                    return smol_help("Invalid field '%s'\n\n", optarg);
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
        return smol_help("Invalid array_length '%s', must be an integer\n\n",
                         argv[optind]);
    options->array_length = atoi(argv[optind]);

    if (strspn(argv[optind + 1], "0123456789") != strlen(argv[optind + 1]))
        return smol_help("Invalid n_iterations '%s', must be an integer\n\n",
                         argv[optind + 1]);
    options->n_iterations = atoi(argv[optind + 1]);
#endif  // PROGRAM_ID

    if (options->verbose) {
        printf("Using these options:\n");
        print_options(*options);
        printf("\n");
    }

    return 0;
}
