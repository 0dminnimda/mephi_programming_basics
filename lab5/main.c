#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
# 1
    file_in - program will read the data from this file
    file_out - program will write the data to this file
# 2
    array_length - number of elements in the generated array
    array_count - number of generated array
# options
    -r --reserve - reverse the sorting direction (form ascending to descending)
    -k --key - which field to use as a sorting key
    -s --sort - what sorting algorithm to use
*/

typedef int sort_id;

sort_id str_to_sort(char *in) {
    return 0;
}

typedef struct Atom {
    int field1;
    char *field2;
    long long field3;
} Atom;

typedef size_t atom_field_offset;

atom_field_offset str_to_atom_field(char *in) {
    return 0;
}

typedef struct Options {
    FILE *file_in;
    FILE *file_out;

    size_t array_length;
    size_t array_count;

    int reserve;
    atom_field_offset key;
    sort_id sort;
} Options;

int main(int argc, char *argv[]) {
    int flags, opt;
    int nsecs, tfnd;

    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "nt:")) != -1) {
        switch (opt) {
            case 'n':
                flags = 1;
                break;
            case 't':
                nsecs = atoi(optarg);
                tfnd = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n", flags, tfnd, nsecs,
           optind);

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    printf("name argument = %s\n", argv[optind]);

    /* Other code omitted */

    exit(EXIT_SUCCESS);
}

#include <getopt.h>
#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for exit */

int main(int argc, char *argv[]) {
    int c;
    int digit_optind = 0;

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"add", required_argument, 0, 0},
            {"append", no_argument, 0, 0},
            {"delete", required_argument, 0, 0},
            {"verbose", no_argument, 0, 0},
            {"create", required_argument, 0, 'c'},
            {"file", required_argument, 0, 0},
            {0, 0, 0, 0}};

        c = getopt_long(argc, argv, "abc:d:012", long_options, &option_index);
        if (c == -1) break;

        switch (c) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg) printf(" with arg %s", optarg);
                printf("\n");
                break;

            case '0':
            case '1':
            case '2':
                if (digit_optind != 0 && digit_optind != this_option_optind)
                    printf("digits occur in two different argv-elements.\n");
                digit_optind = this_option_optind;
                printf("option %c\n", c);
                break;

            case 'a':
                printf("option a\n");
                break;

            case 'b':
                printf("option b\n");
                break;

            case 'c':
                printf("option c with value '%s'\n", optarg);
                break;

            case 'd':
                printf("option d with value '%s'\n", optarg);
                break;

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    // if (optind < argc) {
    //     printf("non-option ARGV-elements: ");
    //     while (optind < argc) printf("%s ", argv[optind++]);
    //     printf("\n");
    // }

    exit(EXIT_SUCCESS);
}
