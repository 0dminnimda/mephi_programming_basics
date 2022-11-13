#include "rational.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct RationalNode_ {
    long long decimal;
    unsigned long long fractional;
    // char *decimal;
    // char *fractional;
} RationalNode_;

int sscan_rational(char *str_ptr, Rational *rat, int *offset) {
    *rat = malloc(sizeof(RationalNode_));
    if (*rat == NULL) return -1;

    (*rat)->decimal = 0;
    (*rat)->fractional = 0;

    // printf("Created!\n");

    int offset1 = 0;
    if (sscanf_s(str_ptr, "%18lld%n", &(*rat)->decimal, &offset1) != 1) return -1;
    str_ptr += offset1;
    // printf("First %lld! Chrs: %d! Rest: %s!\n", (*rat)->decimal, offset1, str_ptr);

    int offset2 = 0;
    int res = sscanf_s(str_ptr, ".%18llu%n", &(*rat)->fractional, &offset2);
    // printf("Second %llu! Chrs: %d! Res %d\n", (*rat)->fractional, offset2, res);
    if (!(res == 0 || res == 1)) return -1;

    // printf("Chrs: %d\n", offset1 + offset2*res);
    *offset = offset1 + offset2*res;

    return 0;
}
/*


    printf("Created!\n");

    int offset = 0;
    if (sscanf_s(str_ptr, "%18lld%n", &(*rat)->decimal, &offset) != 1)
        return -1;
    str_ptr += offset;
    printf("First %lld! Chrs: %d! Rest: %s!\n", (*rat)->decimal, offset1, str_ptr);

    if (str_ptr + offset1 == '.') {
        offset1 += 1;
        int res = sscanf_s(str_ptr + offset1, "%llu%n", &(*rat)->fractional, &offset2);
        printf("Second %llu! Chrs: %d! Res %d\n", (*rat)->fractional, offset2, res);
        if (res == 0 || res == 1) return -1;
        offset2 * res
    } else printf("No second");

    printf("Chrs: %d\n", offset1 + offset2 * res);
    *offset = offset1 + offset2 * res;

*/
void destroy_rational(Rational rat) {
    // free(rat->decimal);
    // free(rat->fractional);
    free(rat);
}

void print_rational(Rational rat) {
    printf("%lld.%llu", rat->decimal, rat->fractional);
}
