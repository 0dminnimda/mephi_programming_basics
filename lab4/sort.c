#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void merge(SORT_ITEM_T *data, SORT_ITEM_T *auxiliary, size_t lo,
                  size_t hi) {
    if (lo >= hi - 1) return;

    size_t mid = (lo + hi) / 2;
    merge(data, auxiliary, lo, mid);
    merge(data, auxiliary, mid, hi);

    size_t pos = lo, lhs = lo, rhs = mid;
    for (;;) {
        if (lhs < mid &&
            (rhs >= hi || !(SORT_GREATER_FUNC(data[lhs], data[rhs])))) {
            auxiliary[pos++] = data[lhs++];
        } else if (rhs < hi) {
            auxiliary[pos++] = data[rhs++];
        } else {
            break;
        }
    }

    memcpy(data + lo, auxiliary + lo, (hi - lo) * sizeof(SORT_ITEM_T));
}

int merge_sort(SORT_ITEM_T *data, size_t len) {
    if (len <= 1) return 0;

    SORT_ITEM_T *auxiliary = malloc(len * sizeof(SORT_ITEM_T));
    if (auxiliary == NULL) return -1;

    // memcpy(auxiliary, data, len * sizeof(SORT_ITEM_T));
    merge(data, auxiliary, 0, len);

    free(auxiliary);
    return 0;
}

#define N 21

int main() {
    int a[N] = {1, 2, 2, 2, 2, 3, 7, 9, 9, 9, 2, 4, 5, 5, 6, 7, 8, 9, 9, 9, 3};

    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    if (merge_sort(a, N)) {
        printf("ERROR: malloc\n");
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
