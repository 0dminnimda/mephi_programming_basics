#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int maximize(int n) {
    int size = ceil(log10((double)n));
    int sorted = 0;
    do {
        sorted = 1;
        int offset = 1;
        for (int i = 0; i < size - 1; i++) {
            int d1 = n / offset % 10;
            int d2 = n / (offset*10) % 10;
            if (d1 < d2) {
                // printf("%d-%d ", d1 * v, d2 * v * 10);
                n = n - d1 * offset + d2 * offset;
                n = n - d2 * offset * 10 + d1 * offset * 10;
                sorted = 0;
            }
            // printf("%d:%d ", d1, d2);
            offset *= 10;
        }
    } while (sorted != 1);
    return n;
}

int main() {
    printf("Hello! Input one integer\n");
    char *line = NULL;
    size_t tmp = 0;
    int len = getline(&line, &tmp, stdin);
    printf("ggg '%s'", line);
    free(line);
    // printf("Minimal digit combination: %d (leading zeros are gone)", maximize(n));
}
