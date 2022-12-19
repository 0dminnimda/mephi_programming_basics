#include "sort_type.h"

#define STR(x) #x

sort_t char2sort(char chr) {
    if (chr == STR(BubbleSort)[0]) return BubbleSort;
    if (chr == STR(DoubleSelectionSort)[0]) return DoubleSelectionSort;
    if (chr == STR(QuickSort)[0]) return QuickSort;
    return SortCount;
}

char *sort2str(sort_t sort) {
    if (sort == BubbleSort) return STR(BubbleSort);
    if (sort == DoubleSelectionSort) return STR(DoubleSelectionSort);
    if (sort == QuickSort) return STR(QuickSort);
    return "InvalidSort";
}
