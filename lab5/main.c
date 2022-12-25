#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VECTOR_PRINT_ERROR(message) fprintf(stderr, "ERROR: %s\n", message)
#include "sort.h"

int read_file_data(Voters voters, Options options) {
    FILE *file = fopen(options.input_file, "r");
    if (file == NULL) return -1;

    vec_clear(voters);

    Voter voter;
    while (fscanf_voter(file, &voter) == 0) vec_push_back(voters, voter);

    fclose(file);
    return 0;
}

int generate_data(Voters voters, Options options) {
    if (vec_resize(voters, options.array_length)) return -1;
    vec_clear(voters);

    Voter voter;
    for (size_t i = 0; i < options.array_length; i++) {
        make_fake_voter(&voter);
        vec_push_back(voters, voter);
    }

    return 0;
}

int get_data(Voters voters, Options options) {
    if (options.input_file == NULL) return generate_data(voters, options);
    return read_file_data(voters, options);
}

void put_data(Voters voters, Options options) {
    if (options.output_file == NULL) return;

    FILE *file = fopen(options.output_file, "w");

    if (file == NULL) {
        fprintf(stderr, "ERROR: Could not open output file\n");
        return;
    }

    for (size_t i = 0; i < vec_length(voters); i++) {
        fprint_voter(file, vec_get(voters, i));
        fprintf(file, "\n");
    }

    fclose(file);
}

double current_time() {
#if __STDC_VERSION__ >= 201112L  // C11
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e+9;
#else
    return clock() / CLOCKS_PER_SEC;
#endif
}

#define TIMEIT(timing, code)              \
    do {                                  \
        double begin = current_time();    \
        code;                             \
        timing += current_time() - begin; \
    } while (0)

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Options options;
    if (parse(argc, argv, &options)) return -1;

    Voters voters;
    if (create_vector(&voters, 0)) return 0;

    char *iter_format =
        options.verbose ? "\nIteration %zu\n" : "Iteration %zu\r";

    double time = 0;
    size_t iter;
    for (iter = 0; iter < options.n_iterations; iter++) {
        if (options.n_iterations > 1) printf(iter_format, iter + 1);

        if (get_data(voters, options)) {
            fprintf(stderr, "ERROR: Could not read or generate data\n");
            return 0;
        }

        if (options.verbose) {
            for (size_t i = 0; i < vec_length(voters); i++) {
                fprint_voter(stdout, vec_get(voters, i));
                printf("\n");
            }
        }

        if (options.verbose) printf("\nSorting ...\n");
        TIMEIT(time, sort(voters, options));
        if (options.verbose) printf("\n");

        if (options.verbose) {
            for (size_t i = 0; i < vec_length(voters); i++) {
                fprint_voter(stdout, vec_get(voters, i));
                printf("\n");
            }
        }

        put_data(voters, options);
    }

    destroy_vector(voters);

#if !(PROGRAM_ID == 1)
    printf("\n");
    printf("On average %.10lf seconds was spent on sorting one array\n",
           time / iter);
    printf("Total work time: %.10lf seconds for %zu iterations\n", time, iter);
#endif  // PROGRAM_ID

    return 0;
}
