#ifndef SORT_ITEM_T
#define SORT_ITEM_T int
// #error You should define 'SORT_ITEM_T' to use sorts
#endif  // SORT_ITEM_T

#ifndef SORT_GREATER_FUNC
#define SORT_GREATER_FUNC(a, b) a > b
#endif  // SORT_GREATER_FUNC

int merge_sort(SORT_ITEM_T *data, size_t len);
