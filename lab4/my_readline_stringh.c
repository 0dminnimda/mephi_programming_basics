#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "my_readline.h"

#define CHUNK_SIZE 2
#define CHUNK_SIZED_STRING_FORMAT "%2[^\n]"

char *my_readline(const char *prompt) {
    if (prompt) printf("%s", prompt);

    char *buf = NULL;
    char *end = NULL;

    int scanf_result = 0;
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
        int scanf_result = scanf(CHUNK_SIZED_STRING_FORMAT, end);

        end[CHUNK_SIZE] = '\0';

        size_t diff = strcspn(end, "\n");
        end += diff;

        // check if we hit the end of the line
        if ((*end == '\n') || (diff != CHUNK_SIZE && *end == '\0'))
            break;
    }

    if (end) *end = '\0';
    if ((end - buf) || (scanf_result != EOF)) return buf;
    free(buf);
    return NULL;
}

int main(int argc, char *argv[]) {
    char *line = my_readline(0);
    printf("Returned ");
    printf("'%s'\n", line);
    free(line);
}
