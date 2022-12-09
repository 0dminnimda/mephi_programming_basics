#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef SORT_ITEM_T
#define SORT_ITEM_T int
#endif  // SORT_ITEM_T

#ifndef SORT_GREATER_FUNC
#define SORT_GREATER_FUNC(a, b) a > b
#endif  // SORT_GREATER_FUNC

static void merge(SORT_ITEM_T *data, SORT_ITEM_T *auxiliary, size_t lo, size_t hi) {
    size_t mid = (lo + hi) / 2;
    printf("Merge %zu %zu -> %zu\n", lo, hi, mid);
    if (lo >= hi - 1) return;

    merge(auxiliary, data, lo, mid);
    merge(auxiliary, data, mid, hi);

    size_t pos = lo, lhs = lo, rhs = mid;
    for (;;) {
        if (rhs < hi && (SORT_GREATER_FUNC(auxiliary[lhs], auxiliary[rhs]))) {
            data[pos++] = auxiliary[rhs++];
        } else if (lhs < mid) {
            data[pos++] = auxiliary[lhs++];
        } else {
            break;
        }
    }
}

int merge_sort(SORT_ITEM_T *data, size_t len) {
    if (len <= 1) return 0;

    SORT_ITEM_T *auxiliary = malloc(len * sizeof(SORT_ITEM_T));
    if (auxiliary == NULL) return -1;

    memcpy(auxiliary, data, len * sizeof(SORT_ITEM_T));
    merge(data, auxiliary, 0, len);

    free(auxiliary);
    return 0;
}

#define N 21

int main()
{
    int a[N] = {1, 2, 2, 2, 2, 3, 7, 9, 9, 9,
                2, 4, 5, 5, 6, 7, 8, 9, 9, 9, 3};

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
