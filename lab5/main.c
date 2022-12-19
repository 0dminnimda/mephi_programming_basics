#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparse.h"


int main(int argc, char *argv[]) {
    Options options;
    return parse(argc, argv, &options);
}
