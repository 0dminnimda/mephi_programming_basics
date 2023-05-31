#include "my_readline.h"

#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 2
#define CHUNK_SIZED_STRING_FORMAT "%2[^\n]%n"

char *readline(const char *prompt) {
    if (prompt) printf("%s", prompt);

    size_t len = 0;
    char *buf = malloc(2 * sizeof(char));
    if (buf == NULL) return NULL;

    // read at most one symbol to set offset and result - representing state
    // current state can be eof, \n, normal input or nothing
    int scanf_result = scanf("%1[\n]", buf);

    if (scanf_result == 1) {
        *buf = '\0';
        return buf;
    } else if (scanf_result == EOF) {
        free(buf);
        return NULL;
    }

    while (1) {
        // extend the memory by one chunk
        char *new_buf = realloc(buf, (len + 1 + CHUNK_SIZE) * sizeof(char));
        if (new_buf == NULL) {
            free(buf);
            return NULL;
        }
        buf = new_buf;

        // read new chunk
        int offset = 0;
        scanf_result = scanf(CHUNK_SIZED_STRING_FORMAT, buf + len, &offset);

        // check if we hit the end of the line
        if (scanf_result != 1 || offset == 0) break;
        len += offset;
    }

    if (len > 0) {
        // consume the potential \n
        char junk[2];
        scanf("%1[\n]", junk);
    } else if (scanf_result == EOF) {
        free(buf);
        return NULL;
    }
    *(buf + len) = '\0';
    return buf;
}
