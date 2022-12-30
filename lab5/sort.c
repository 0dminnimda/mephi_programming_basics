#include "sort.h"

#include <stdlib.h>
#include <string.h>

typedef int void_cmp(const void *, const void *);

void *void_add(void *ptr, long long offset, size_t size) {
    return (char *)ptr + offset * (long long)size;
}

void *void_inc(void **ptr, size_t size) {
    return *ptr = void_add(*ptr, 1, size);
}

void *void_dec(void **ptr, size_t size) {
    return *ptr = void_add(*ptr, -1, size);
}

void swap(void *a, void *b, size_t size) {
    char *temp = malloc(size);
    if (temp != NULL) {
        memcpy(temp, a, size);
        memcpy(a, b, size);
        memcpy(b, temp, size);
    }
    free(temp);
}

void bubble_sort(void *data, size_t length, size_t size, void_cmp *cmp) {
    for (size_t i = 0; i < length - 1; i++) {
        int swapped = 0;

        for (size_t j = 0; j < length - i - 1; j++) {
            void *a = void_add(data, j, size);
            void *b = void_add(data, j + 1, size);

            if (cmp(a, b) > 0) {
                swap(a, b, size);
                swapped = 1;
            }
        }

        if (!swapped) break;
    }
}

void minmax(void *start, void *end, void_cmp *cmp, void **min_v, void **max_v,
            size_t size) {
    while (start <= end) {
        if (cmp(start, *min_v) < 0)
            *min_v = start;
        else if (cmp(start, *max_v) > 0)
            *max_v = start;
        void_inc(&start, size);
    }
}

void double_selection_sort(void *data, size_t length, size_t size,
                           void_cmp *cmp) {
    void *start = data, *end = void_add(data, length - 1, size);

    while (start < end) {
        void *min = start;
        void *max = end;
        minmax(start, end, cmp, &min, &max, size);

        if (min != start) swap(min, start, size);
        if (max != end) swap(max == start ? min : max, end, size);
        void_inc(&start, size);
        void_dec(&end, size);
    }
}

void sort(Voters voters, Options options) {
    void_cmp *cmp = (void_cmp *)field2cmp(options.field);
    size_t length = vec_length(voters);

    if (options.sort == BubbleSort) {
        bubble_sort(vec_data(voters), length, sizeof(Voter), cmp);
    } else if (options.sort == DoubleSelectionSort) {
        double_selection_sort(vec_data(voters), length, sizeof(Voter), cmp);
    } else if (options.sort == QuickSort) {
        qsort(vec_data(voters), length, sizeof(Voter), cmp);
    }

    if (options.reverse) {
        size_t i = 0, j = length - 1;
        while (i < j) {
            Voter tmp = vec_get(voters, i);
            vec_set(voters, i++, vec_get(voters, j));
            vec_set(voters, j--, tmp);
        }
    }
}
