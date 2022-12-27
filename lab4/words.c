#include "words.h"

#include <stdio.h>

#if PROGRAM_ID == 1
    #include <string.h>
#else
    #include "my_string.h"
#endif  // PROGRAM_ID

Words split(char *line) {
    Words words;
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

int maxi(int a, int b) { return (a > b) ? a : b; }
#define STR_PRINT(...) maxi(sprintf(__VA_ARGS__), 0)

char *sprint_words(Words words, size_t len) {
    char *result = malloc(len * sizeof(char));
    if (result == NULL) return NULL;
    *result = '\0';

    char *builder = result;
    for (size_t i = 0; i < get_length(words); i++) {
        if (*get_item(words, i) != '\0') {
            if (builder - result) sprintf(builder++, " ");
            builder += STR_PRINT(builder, "%s", get_item(words, i));
        }
    }
    return result;
}
