#include <stdio.h>
#include <stdlib.h>
#include "my_readline.h"
#include "my_string.h"

#define VECTOR_ITEM char*
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
#define FIRST_CHAR 0

typedef unsigned long long alphabet_sub_t;

typedef struct alphabet_t {
    alphabet_sub_t lo;
    alphabet_sub_t hi;
} alphabet_t;

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
        printf("%c'%s'", ' '*(i != 0), get_item(words, i));
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
        printf("%s ---- ", word);
        while (*word != '\0') {
            char coded = *word - FIRST_CHAR;
            printf("%d %c %d %d\n", (int)*word, *word, coded < BITS_IN_LL, (char)(coded - BITS_IN_LL*(coded >= BITS_IN_LL)));
            if (coded < BITS_IN_LL)
                alphabets[i].lo |= ((alphabet_sub_t)1 << coded);
            else
                alphabets[i].hi |= ((alphabet_sub_t)1 << (coded - BITS_IN_LL));
            word++;
        }

#if 1

        // debug output
        printf("\n");
        for (size_t j = '!'; j < 2*BITS_IN_LL; j++) {
            printf("%c", (char)(j + FIRST_CHAR));
        }
        printf("\n");
        for (size_t j = '!'; j < BITS_IN_LL; j++) {
            printf("%d", (alphabets[i].lo & ((alphabet_sub_t)1 << j)) != 0);
        }
        for (size_t j = 0; j < BITS_IN_LL; j++) {
            printf("%d", (alphabets[i].hi & ((alphabet_sub_t)1 << j)) != 0);
        }
        printf("\n");

#else

#endif

        printf("%llu %llu :\n", alphabets[i].lo, alphabets[i].hi);
        for (size_t j = 0; j < BITS_IN_LL; j++) {
            char decoded = j + FIRST_CHAR;
            if (alphabets[i].lo & ((alphabet_sub_t)1 << j))
                printf("%d %c %d\n", (int)decoded, decoded, (char)j);
                // printf("%c", decoded);
        }
        printf("s\n");
        for (size_t j = 0; j < BITS_IN_LL; j++) {
            char decoded = j + FIRST_CHAR + BITS_IN_LL;
            if (alphabets[i].hi & ((alphabet_sub_t)1 << j))
                printf("%d %c %d\n", (int)decoded, decoded, (char)j);
                // printf("%c", decoded);
        }
        printf("\n");
    }

    free(alphabets);
    free(words);
    free(line);
    return 0;
}
