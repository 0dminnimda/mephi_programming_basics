#include <stdio.h>
#include <stdlib.h>

#include "my_readline.h"
#include "my_string.h"

#define VECTOR_ITEM char *
#define VECTOR_ITEM_DESTRUCTOR(item) free(item)

#include "vector.h"

Vector split(char *line) {
    Vector words;
    if (create(&words, 0)) return NULL;

    while (1) {
        if (*line == ' ' || *line == '\t') *line++ = '\0';
        while ((*line != '\0') && (*line == ' ' || *line == '\t')) line++;
        if (*line == '\0') break;

        push_back(words, line);
        line += strcspn(line, " \t");
    }

    return words;
}

typedef unsigned long long alphabet_sub_t;

#define BITS_IN_SUB_T 64
#define MASK(shift) ((alphabet_sub_t)1 << (shift))

#define SUB_COUNT 4
typedef alphabet_sub_t alphabet_t[SUB_COUNT];

int alphabet_geq(alphabet_t alphabet1, alphabet_t alphabet2) {
    return ((alphabet1[0] >= alphabet2[0]) && (alphabet1[1] >= alphabet2[1]) &&
            (alphabet1[2] >= alphabet2[2]) && (alphabet1[3] >= alphabet2[3]));
}

int alphabet_eq(alphabet_t alphabet1, alphabet_t alphabet2) {
    return ((alphabet1[0] == alphabet2[0]) && (alphabet1[1] == alphabet2[1]) &&
            (alphabet1[2] == alphabet2[2]) && (alphabet1[3] == alphabet2[3]));
}

// int alphabet_cpy(alphabet_t *alphabet1, alphabet_t *alphabet2) {
//     return memcpy(alphabet1, alphabet2, SUB_COUNT * sizeof(alphabet_sub_t));
// }

alphabet_t *generate_alphabets(Vector words) {
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

void print_word_alphabets(Vector words, alphabet_t *alphabets) {
    printf("Words use those alphabets:\n");
    for (size_t i = 0; i < get_length(words); i++) {
        printf("'%s' uses: ", get_item(words, i));

        printf("'");
        for (char j = 0; j < SUB_COUNT; j++)
            for (char bit = 0; bit < BITS_IN_SUB_T; bit++)
                if (alphabets[i][j] & MASK(bit))
                    printf("%c", bit + j * BITS_IN_SUB_T);
        printf("' ");

        printf("(");
        for (size_t j = 0; j < SUB_COUNT; j++)
            printf("%c%llu", ' ' * (j != 0), alphabets[i][j]);
        printf(")\n");
    }
}

int remove_non_unique_words(Vector words, alphabet_t *alphabets) {
    int *non_unique = malloc(get_length(words) * sizeof(int));
    if (get_length(words) && non_unique == NULL) return -1;

    for (size_t i = 0; i < get_length(words); i++) non_unique[i] = 0;

    for (size_t i = 0; i < get_length(words); i++) {
        if (non_unique[i]) continue;        
        for (size_t j = i + 1; j < get_length(words); j++) {
            if (!non_unique[j] && alphabet_eq(alphabets[i], alphabets[j])) {
                non_unique[i] = 1;
                non_unique[j] = 1;
            }
        }
    }
    for (size_t i = 0; i < get_length(words); i++) {
        if (non_unique[i]) {
            *get_item(words, i) = '\0';
        }
            // alphabet_cpy(alphabets[(*new_size)++], alphabets[i]);
    }
    return 0;
}

int main(void) {
    printf("Input words\n");
    char *line = my_readline(NULL);
    if (!line) {
        printf("ERROR: Could not read a line\n");
        return 0;
    }
    printf("I got the string '%s'\n", line);

    Vector words = split(line);
    if (!words) {
        printf("ERROR: Could not split the line into words\n");
        return 0;
    }

    printf("The words I found:\n");
    for (size_t i = 0; i < get_length(words); i++) {
        printf("%c'%s'", ' ' * (i != 0), get_item(words, i));
    }
    printf("\n");

    alphabet_t *alphabets = generate_alphabets(words);
    if (!alphabets) {
        printf("ERROR: could not generate alphabets\n");
        return 0;
    }
    print_word_alphabets(words, alphabets);

    if (remove_non_unique_words(words, alphabets)) {
        printf("ERROR: could not remove non unique words\n");
        return 0;
    }

    printf("Result:\n");
    size_t shown = 0;
    for (size_t i = 0; i < get_length(words); i++) {
        if (*get_item(words, i))
            printf("%c%s", ' ' * (shown++ != 0), get_item(words, i));
    }
    printf("\n");

    free(alphabets);
    free(words);
    free(line);
    return 0;
}

// abs absb absbsbsbsbsb aabssbsbasbab absfg none one neon gg erloftkes;f k'pwae;3 r3k
