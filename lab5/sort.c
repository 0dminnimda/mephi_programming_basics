#include "sort.h"

#include <stdlib.h>

void swap(Voter *a, Voter *b) {
    Voter temp = *a;
    *a = *b;
    *b = temp;
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

}

void bubble_sort(Voters voters, cmp_func_t *cmp) {
    for (size_t i = 0; i < vec_length(voters) - 1; i++) {
        int swapped = 0;

        for (size_t j = 0; j < vec_length(voters) - i - 1; j++) {
            Voter *a = vec_at(voters, j);
            Voter *b = vec_at(voters, j + 1);

            if (cmp(a, b) > 0) {
                swap(a, b);
                swapped = 1;
            }
        }

        if (!swapped) break;
    }
}

void minmax(Voter *start, Voter *end, cmp_func_t *cmp, Voter **min_v,
            Voter **max_v) {
    while (start <= end) {
        if (cmp(start, *min_v) < 0)
            *min_v = start;
        else if (cmp(start, *max_v) > 0)
            *max_v = start;
        start++;
    }
}

void double_selection_sort(Voters voters, cmp_func_t *cmp) {
    Voter *start = vec_at(voters, 0),
          *end = vec_at(voters, vec_length(voters) - 1);

    while (start < end) {
        Voter *min = start;
        Voter *max = end;
        minmax(start, end, cmp, &min, &max);

        if (min != start) swap(min, start);
        if (max != end) swap(max == start ? min : max, end);
        start++, end--;
    }
}

void sort(Voters voters, Options options) {
    cmp_func_t *cmp = field2cmp(options.field);

    if (options.sort == BubbleSort) {
        bubble_sort(voters, cmp);
    } else if (options.sort == DoubleSelectionSort) {
        double_selection_sort(voters, cmp);
    } else if (options.sort == QuickSort) {
        qsort(vec_data(voters), vec_length(voters), sizeof(Voter),
              (int (*)(const void *, const void *))cmp);
    }

    if (options.reverse) {
        size_t i = 0, j = vec_length(voters) - 1;
        while (i < j) {
            Voter tmp = vec_get(voters, i);
            vec_set(voters, i++, vec_get(voters, j));
            vec_set(voters, j--, tmp);
        }
    }
}
