#include "rational.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct RationalNode_ {
    long long decimal;
    unsigned long long fractional;
} RationalNode_;

int sscan_rational(char *str_ptr, Rational *rat, int *offset) {
    *rat = malloc(sizeof(RationalNode_));
    if (*rat == NULL) return -1;

    (*rat)->decimal = 0;
    (*rat)->fractional = 0;

    int offset1 = 0, offset2 = 0;
    int dec = sscanf_s(str_ptr, "%18lld%n", &(*rat)->decimal, &offset1);
    str_ptr += offset1;
    int frac = sscanf_s(str_ptr, ".%18llu%n", &(*rat)->fractional, &offset2);
    if (dec == 1) {
        if (frac != 0 && frac != 1) return -1;
    } else if (dec == 0) {
        if (frac != 1) return -1;
    } else {
        return -1;
    }

    *offset = offset1 * dec + offset2 * frac;

    return 0;
}

void destroy_rational(Rational rat) { free(rat); }

void print_rational(Rational rat) {
    printf("%lld.%llu", rat->decimal, rat->fractional);
}
