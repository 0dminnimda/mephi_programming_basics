#include "my_readline.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 2
#define CHUNK_SIZED_STRING_FORMAT "%2[^\n]%n"

char *readline(const char *prompt) {
    if (prompt) printf("%s", prompt);

    char *buf = NULL;
    char *end = NULL;

    int scanf_result = 0;

    char new_line[2];
    if (scanf("%1[\n]", new_line) == EOF) return NULL;

    while (1) {
        // extend the memory by one chunk
        char *new_buf = realloc(buf, (end - buf + CHUNK_SIZE) * sizeof(char));
        if (new_buf == NULL) {
            free(buf);
            return NULL;
        }
        end = new_buf + (end - buf);
        buf = new_buf;

        // read new chunk
        int offset = 0;
        scanf_result = scanf(CHUNK_SIZED_STRING_FORMAT, end, &offset);

        // check if we hit the end of the line
        if (scanf_result != 1 || offset == 0) break;
        end += offset;
    }

    if ((end - buf == 0) && (scanf_result == EOF)) {
        free(buf);
        return NULL;
    }
    *end = '\0';
    return buf;
}
