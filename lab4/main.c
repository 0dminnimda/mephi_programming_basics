#include <stdio.h>
#include <stdlib.h>

#include "my_readline.h"
#include "my_string.h"
#include "words.h"

typedef unsigned long long alphabet_sub_t;

#define BITS_IN_SUB_T 64
#define MASK(shift) ((alphabet_sub_t)1 << (shift))

// how many llu we need to cover all char values? (usually 4)
#define SUB_COUNT (1 << (sizeof(char) * 8)) / (sizeof(unsigned long long) * 8)
typedef alphabet_sub_t alphabet_t[SUB_COUNT];

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

int remove_non_unique_words(Words words) {
    alphabet_t *alphabets = generate_alphabets(words);
    if (!alphabets) {
        free(alphabets);
        return -1;
    }

    int *non_unique = malloc(get_length(words) * sizeof(int));
    if (get_length(words) && non_unique == NULL) {
        free(alphabets);
        return -1;
    }

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

    for (size_t i = 0; i < get_length(words); i++)
        if (non_unique[i]) *get_item(words, i) = '\0';

    free(alphabets);
    return 0;
}

int main(void) {
    printf("Input words and I will leave only unique ones!\n");

    char *line = NULL;
    Words words = NULL;

    while (1) {        
        free(words);
        free(line);

        line = my_readline(">>> ");
        if (!line) {
            printf("ERROR: Could not read a line\n");
            break;
        }

        words = split(line);
        if (!words) {
            printf("ERROR: Could not split the line into words\n");
            break;
        }

        printf("I got those words:\n");
        print_words(words);

        if (remove_non_unique_words(words)) {
            printf("ERROR: could not remove non unique words\n");
            break;
        }

        printf("And after removing non-unique words we have:\n");
        print_words(words);
    }

    free(words);
    free(line);
    return 0;
}

// abs absb absbsbsbsbsb aabssbsbasbab absfg none one neon gg erloftkes;f k'pwae;3 r3k
