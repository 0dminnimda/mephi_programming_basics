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

void print_words(Words words) {
    size_t shown = 0;
    printf("\"");
    for (size_t i = 0; i < get_length(words); i++) {
        if (*get_item(words, i))
            printf("%c%s", ' ' * (shown++ != 0), get_item(words, i));
    }
    printf("\"\n");
}
