#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 2
#define CHUNK_SIZED_STRING_FORMAT "%2[^\n]"

char *my_readline(char *prompt) {
    if (prompt)
        printf("%s", prompt);

    char *buf = NULL;
    char *end = NULL;

    int scanf_result = 0;
    int end_reached = 0;
    while (!end_reached) {        
        // extend the memory by one chunk
        printf("New length %d, new size %d\n", end - buf + CHUNK_SIZE, (end - buf + CHUNK_SIZE) * sizeof(char));
        char *new_buf = (char*)realloc(buf, (end - buf + CHUNK_SIZE) * sizeof(char));
        if (new_buf == NULL) {
            free(buf);
            return NULL;
        }
        end = new_buf + (end - buf);
        buf = new_buf;

        // read new chunk
        int scanf_result = scanf(CHUNK_SIZED_STRING_FORMAT, end);
        printf("Read '%s'\n", end);

        printf("Scanf result %d\n", scanf_result);

        // check if we hit the end on the line
        char *pos;
        for (pos = end; pos < end + CHUNK_SIZE; pos++) {
            printf("Char checked '%c'\n", *pos);
            if (*pos == '\0' || *pos == '\n') {
                end_reached = 1;
                break;
            }
        }
        end = pos;
        printf("New start %p, end %p, len %d\n", buf, end, end - buf);
    }

    if ((end - buf) || (scanf_result != EOF))
        return buf;
    printf("Null the result\n");
    free(buf);
    return NULL;
}

int main(int argc, char *argv[])
{
    char *line = my_readline(0);
    printf("Returned ");
    printf("'%s'\n", line);
    free(line);
}
