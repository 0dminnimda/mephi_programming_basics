typedef enum sort_t {
    BubbleSort,
    DoubleSelectionSort,
    QuickSort,
    SortCount
} sort_t;

sort_t char2sort(char chr);
char *sort2str(sort_t sort);
