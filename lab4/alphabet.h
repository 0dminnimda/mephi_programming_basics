#include "words.h"

#define MASK(shift) ((alphabet_sub_t)1 << (shift))

#define BITS_IN_SUB_T (sizeof(alphabet_sub_t) * 8)
// how many sub type variables we need to cover all char values? (usually 4)
#define SUB_COUNT ((1 << (sizeof(char) * 8)) / BITS_IN_SUB_T)

typedef unsigned long long alphabet_sub_t;
typedef alphabet_sub_t alphabet_t[SUB_COUNT];

alphabet_t *generate_alphabets(Words words);
int alphabet_eq(alphabet_t alphabet1, alphabet_t alphabet2);
