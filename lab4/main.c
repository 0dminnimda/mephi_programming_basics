#include <stdio.h>
#include <stdlib.h>

#if PROGRAM_ID == 1
    #include <readline/readline.h>
#else
    #include "my_readline.h"
#endif  // PROGRAM_ID

#include "alphabet.h"
#include "words.h"

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

        line = readline(">>> ");
        if (!line) {
            printf("ERROR: Could not read a line\n");
            break;
        }
        printf("\nThe line I got: \"%s\"\n", line);

        words = split(line);
        if (!words) {
            printf("ERROR: Could not split the line into words\n");
            break;
        }

        printf("\nI got those words:\n");
        print_words(words);

        if (remove_non_unique_words(words)) {
            printf("ERROR: could not remove non unique words\n");
            break;
        }

        printf("\nAnd after removing non-unique words we have:\n");
        print_words(words);
    }

    free(words);
    free(line);
    return 0;
}

// abs absb absbsbsbsbsb aabssbsbasbab absfg none one neon gg erloftkes;f k'pwae;3 r3k
