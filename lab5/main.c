#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VECTOR_PRINT_ERROR(message) printf("ERROR: %s\n", message)
#include "argparse.h"

Voters read_file_data(Options options) {
    Voters voters;
    if (create_vector(&voters, 0)) return NULL;

    FILE *input_file;
    input_file = fopen(options.input_file, "r");

    if (input_file == NULL) return NULL;

    Voter voter;
    while (fscanf_voter(input_file, &voter) == 0) vec_push_back(voters, voter);

    fclose(input_file);
    return voters;
}

Voters generate_data(Options options) {
    Voters voters;
    if (create_vector(&voters, 0)) return NULL;

    Voter voter;
    for (size_t i = 0; i < options.array_length; i++) {
        make_fake_voter(&voter);
        vec_push_back(voters, voter);
    }

    return voters;
}

Voters get_data(Options options) {
    if (options.input_file) return read_file_data(options);
    return generate_data(options);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Options options;
    if (parse(argc, argv, &options)) return -1;

}
