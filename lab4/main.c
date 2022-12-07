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

#define BITS_IN_LL 64

typedef unsigned long long alphabet_sub_t;

typedef struct alphabet_t {
    alphabet_sub_t lo;
    alphabet_sub_t hi;
} alphabet_t;

#define MASK(shift) ((alphabet_sub_t)1 << (shift))

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

    alphabet_t *alphabets = malloc(get_length(words) * sizeof(alphabet_t));
    if (get_length(words) && alphabets == NULL) {
        printf("ERROR: could not allocate new memory\n");
        return 0;
    }

    printf("Words use those alphabets:\n");
    for (size_t i = 0; i < get_length(words); i++) {
        alphabets[i].lo = 0;
        alphabets[i].hi = 0;

        char *word = get_item(words, i);
        printf("'%s' uses: '", word);

        while (*word != '\0') {
            if (*word < BITS_IN_LL)
                alphabets[i].lo |= MASK(*word);
            else
                alphabets[i].hi |= MASK(*word - BITS_IN_LL);
            word++;
        }

        for (char j = 0; j < BITS_IN_LL; j++)
            if (alphabets[i].lo & MASK(j)) printf("%c", j);
        for (char j = 0; j < BITS_IN_LL; j++)
            if (alphabets[i].hi & MASK(j)) printf("%c", j + BITS_IN_LL);
        printf("' (%llu %llu)\n", alphabets[i].lo, alphabets[i].hi);
    }

    free(alphabets);
    free(words);
    free(line);
    return 0;
}
