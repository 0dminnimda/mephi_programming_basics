#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VECTOR_PRINT_ERROR(message) printf("ERROR: %s\n", message)
#include "argparse.h"

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


int main(int argc, char *argv[]) {
    srand(time(NULL));

    Options options;
    if (parse(argc, argv, &options)) return -1;

}
