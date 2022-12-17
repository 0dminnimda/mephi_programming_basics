#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if PROGRAM_ID == 1
    #include <readline/readline.h>
#else
    #include "my_readline.h"
#endif  // PROGRAM_ID

#include "alphabet.h"
#include "words.h"

double current_time() {
#if __STDC_VERSION__ >= 201112L  // C11
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e+9;
#else
    return clock() / CLOCKS_PER_SEC;
#endif
}

#define TIMEIT(timing) ;(timing += current_time() - begin, begin = current_time())

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

    free(non_unique);
    free(alphabets);
    return 0;
}

int main(void) {
    printf("Input words and I will leave only unique ones!\n");

    char *line = NULL;
    Words words = NULL;

    while (1) {
        double read_time = 0;
        double work_time = 0;
        double begin = current_time();

        line = readline(">>> ") TIMEIT(read_time);
        if (!line) {
            printf("ERROR: Could not read a line\n");
            break;
        }

        words = split(line) TIMEIT(work_time);
        if (!words) {
            printf("ERROR: Could not split the line into words\n");
            break;
        }

        printf("\nWords found: ");
        print_words(words);

        if (remove_non_unique_words(words)) {
            printf("ERROR: could not remove non unique words\n");
            break;
        }
        TIMEIT(work_time);

        printf("Only-unique words: ");
        print_words(words);

        printf(
            "\n"
            "Reading the input: %.10lf seconds\n"
            "The actual task: %.10lf seconds\n"
            "Total: %.10lf seconds\n\n",
            read_time, work_time, read_time + work_time);

        destroy_vector(words);
        words = NULL;
        free(line);
        line = NULL;
    }

    destroy_vector(words);
    free(line);

    return 0;
}
