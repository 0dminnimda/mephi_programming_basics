#include <stdio.h>

#ifndef SORT_ITEM_T
#define SORT_ITEM_T int
#endif  // SORT_ITEM_T

int greater(SORT_ITEM_T *start1, SORT_ITEM_T *start2) {
    return *start1 > *start2;
}

void merge_ascending_sequences(SORT_ITEM_T *start1, SORT_ITEM_T *end1, SORT_ITEM_T *start2, SORT_ITEM_T *end2) {
    while ((start1 < end1) && (start2 < end2)) {
        if (greater(start1, start2)) {
            SORT_ITEM_T tmp = *start1;
            *start1 = *start2;
            *start2 = tmp;
            start2++;
        } else {
            start1++;
        }
    }
}

int main()
{
    int a[20] = {1, 2, 2, 2, 2, 3, 7, 9, 9, 9,
                 2, 4, 5, 5, 6, 7, 8, 9, 9, 9};

    for (int i = 0; i < 20; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    merge_ascending_sequences(a, a + 10, a + 10, a + 20);

    for (int i = 0; i < 20; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}
