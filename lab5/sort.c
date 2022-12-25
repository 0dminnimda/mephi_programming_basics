#include "sort.h"

#include <stdlib.h>

void bubble_sort(Voters voters, cmp_func_t *cmp) {
    printf("BubbleSort is not implemented yet\n");
}

void double_selection_sort(Voters voters, cmp_func_t *cmp) {
    printf("DoubleSelectionSort is not implemented yet\n");
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
