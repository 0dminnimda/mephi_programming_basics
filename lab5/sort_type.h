typedef enum sort_id {
    BubbleSort,
    DoubleSelectionSort,
    QuickSort,
    SortCount
} sort_id;

sort_id char2sort(char chr);
char *sort2str(sort_id sort);
