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

    free(words);
    free(line);
    return 0;
}
