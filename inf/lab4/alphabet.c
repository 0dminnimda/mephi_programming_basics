#include "alphabet.h"

#include <stdlib.h>

alphabet_t *generate_alphabets(Words words) {
    alphabet_t *alphabets = malloc(get_length(words) * sizeof(alphabet_t));
    if (get_length(words) && alphabets == NULL) return NULL;

    for (size_t i = 0; i < get_length(words); i++) {
        for (size_t j = 0; j < SUB_COUNT; j++) alphabets[i][j] = 0;

        unsigned char *word = (unsigned char *)get_item(words, i);
        while (*word != '\0') {
            if ((*word / BITS_IN_SUB_T) < SUB_COUNT)
                alphabets[i][*word / BITS_IN_SUB_T] |=
                    MASK(*word % BITS_IN_SUB_T);
            word++;
        }
    }
    return alphabets;
}

int alphabet_eq(alphabet_t alphabet1, alphabet_t alphabet2) {
    return ((alphabet1[0] == alphabet2[0]) && (alphabet1[1] == alphabet2[1]) &&
            (alphabet1[2] == alphabet2[2]) && (alphabet1[3] == alphabet2[3]));
}
