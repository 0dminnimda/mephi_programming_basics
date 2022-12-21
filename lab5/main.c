#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_PRINT_ERROR(message) printf("ERROR: %s\n", message)
#include "argparse.h"


int main(int argc, char *argv[]) {
    Options options;
    if (parse(argc, argv, &options)) return -1;

}
