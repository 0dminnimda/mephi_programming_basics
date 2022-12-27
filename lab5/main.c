#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VECTOR_PRINT_ERROR(message) fprintf(stderr, "ERROR: %s\n", message)
#include "sort.h"

#define SPACES " \t"

int read_file_data(Voters voters, Options options) {
    FILE *file = fopen(options.input_file, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Could not open input file (%s)\n",
                options.input_file);
        return -1;
    }

    vec_clear(voters);

    int return_code = 0;
    size_t lineno = 0;
    Voter voter;

    char line[MAX_VOTER_LINE_LENGTH];
    while (fgets(line, MAX_VOTER_LINE_LENGTH, file) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        lineno++;

        int succ = 0;
        if (sscanf_voter(line, &voter) == 0) {
            if (vec_push_back(voters, voter)) {
                fprintf(stderr, "ERROR: Could not read data\n");
                return_code = -1;
                break;
            } else {
                succ = 1;
            }
        } else if (options.warn && strspn(line, SPACES) != strlen(line)) {
            fprintf(stderr, "WARNING: Ignoring invalid data \"%s\" at %s:%zu\n",
                    line, options.input_file, lineno);
        }
        if (!succ) free(voter.name);
    }

    fclose(file);
    return return_code;
}

int generate_data(Voters voters, Options options) {
    if (vec_resize(voters, options.array_length)) {
        fprintf(stderr, "ERROR: Could not generate data\n");
        return -1;
    }
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
        fprintf(stderr, "ERROR: Could not open output file (%s)\n",
                options.output_file);
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

    int return_code = 0;
    double time = 0;
    size_t iter;
    for (iter = 0; iter < options.n_iterations; iter++) {
        if (options.n_iterations > 1) printf(iter_format, iter + 1);

        if (get_data(voters, options)) {
            return_code = -1;
            break;
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

    if (return_code) return return_code;

#if !(PROGRAM_ID == 1)
    printf("\n");
    printf("On average %.10lf seconds was spent on sorting one array\n",
           time / iter);
    printf("Total work time: %.10lf seconds for %zu iterations\n", time, iter);
#endif  // PROGRAM_ID

    return 0;
}
