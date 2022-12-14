#include "my_readline.h"

#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 2
#define CHUNK_SIZED_STRING_FORMAT "%2[^\n]%n"

static int scan_any(char *str, int *offset) {
    int scanf_result;

    scanf_result = scanf("%1[\n]%n", str, offset);
    if (scanf_result == 1) return scanf_result;

    scanf_result = scanf("%1[^\n]%n", str, offset);
    if (scanf_result == 1) return scanf_result;

    *offset = 0;
    return scanf_result;
}

char *readline(const char *prompt) {
    if (prompt) printf("%s", prompt);

    // read at most one symbol + null terminator to check our current state
    // is it eof, \n, normal input or nothing
    char *buf = malloc(2 * sizeof(char));
    if (buf == NULL) return NULL;
    char *end = buf;

    int offset = 0;
    int scanf_result = scan_any(end, &offset);
    printf("  %d %d - %c %d\n", scanf_result, offset, *end, (int)*end);

    offset = offset != 0;
    if (*end == '\n') offset = 0;

    while (scanf_result == 1 && offset != 0) {
        end += offset;

        // extend the memory by one chunk
        char *new_buf = realloc(buf, (end - buf + CHUNK_SIZE) * sizeof(char));
        if (new_buf == NULL) {
            free(buf);
            return NULL;
        }
        end = new_buf + (end - buf);
        buf = new_buf;

        // read new chunk
        offset = 0;
        scanf_result = scanf(CHUNK_SIZED_STRING_FORMAT, end, &offset);
    }

    if (*end != '\n') {
        char junk[2];
        scanf("%1[\n]", junk);
    }

    if ((end - buf == 0) && (scanf_result == EOF)) {
        free(buf);
        return NULL;
    }
    *end = '\0';
    return buf;
}
