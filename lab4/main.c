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

#define SUB_COUNT 2
typedef alphabet_sub_t alphabet_t[SUB_COUNT];

alphabet_t *generate_alphabets(Vector words) {
    alphabet_t *alphabets = malloc(get_length(words) * sizeof(alphabet_t));
    if (get_length(words) && alphabets == NULL) {
        printf("ERROR: could not allocate new memory\n");
        return 0;
    }

    for (size_t i = 0; i < get_length(words); i++) {
        for (size_t j = 0; j < SUB_COUNT; j++)
            alphabets[i][j] = 0;

        char *word = get_item(words, i);
        while (*word != '\0') {
            if ((*word / BITS_IN_SUB_T) < SUB_COUNT)
                alphabets[i][*word / BITS_IN_SUB_T] |= MASK(*word % BITS_IN_SUB_T);
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
                if (alphabets[i][j] & MASK(bit)) printf("%c", bit + j*BITS_IN_SUB_T);
        printf("' ");

        printf("(");
        for (size_t j = 0; j < SUB_COUNT; j++)
            printf("%c%llu", ' ' * (j != 0), alphabets[i][j]);
        printf(")\n");
    }
}

int main(int argc, char *argv[]) {
    printf("Input words\n");
    char *line = my_readline(NULL);
    if (!line) {
        printf("Could not read a line\n");
        return 0;
    }
    printf("I got the string '%s'\n", line);

    Vector words = split(line);
    if (!words) {
        printf("Could not split the line into words\n");
        return 0;
    }

    printf("The words I found:\n");
    for (size_t i = 0; i < get_length(words); i++) {
        printf("%c'%s'", ' ' * (i != 0), get_item(words, i));
    }
    printf("\n");

    alphabet_t *alphabets = generate_alphabets(words);
    print_word_alphabets(words, alphabets);

    free(alphabets);
    free(words);
    free(line);
    return 0;
}
