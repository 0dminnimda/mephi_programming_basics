#include "my_readline.h"

#include <stdio.h>
#include <stdlib.h>

#define STR(x) #x
#define CHUNK_SIZE 2
#define CHUNK_SIZED_STRING_FORMAT "%2[^\n]%n"

char *readline(const char *prompt) {
    if (prompt) printf("%s", prompt);

    char *buf = NULL, *end = buf;
    int scanf_result = 0;

    // set up format and chunk_sz to read at most one symbol + null terminator
    // to check our current state - is it eof, \n, normal input or nothing
    char *format = "%1s%n";
    size_t chunk_sz = 3;

    // char *buf = malloc(2 * sizeof(char));
    // char *end = buf;
    // if (scanf("%1s%n", end, &offset) == EOF) return NULL;
    // if (offset == 0) {}

    while (1) {
        // extend the memory by one chunk
        char *new_buf = realloc(buf, (end - buf + chunk_sz) * sizeof(char));
        if (new_buf == NULL) {
            free(buf);
            return NULL;
        }
        end = new_buf + (end - buf);
        buf = new_buf;

        // read new chunk
        int offset = 0;
        scanf_result = scanf(CHUNK_SIZED_STRING_FORMAT, end, &offset);
        printf("  %zu : %d %d\n", chunk_sz, scanf_result, offset);

        // reset format and chunk_sz to the normal values
        format = "%" STR(CHUNK_SIZE) "[^\n]%n";
        chunk_sz = CHUNK_SIZE;

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
