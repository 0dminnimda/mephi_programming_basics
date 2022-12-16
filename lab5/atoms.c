#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int atom_greater(Atom atom1, Atom atom2) {
    return (*atom1.greater)(atom1, atom2);
}

typedef struct Atom {
    void *data;
    int (*greater)(void *a, void *b);
    void (*print)(void *it);
} Atom;

#define DEFINE_ATOM(name, type, greater, format) \
int name##_greater(void *a_ptr, void *b_ptr) { \
    type a = *(type *)a, b = *(type *)b; \
    return (greater); \
} \
void name##_print(void *it) { \
    printf(format, *(type *)it); \
} \
Item name##_atom(type it) { \
    return .{it, name##_greater, name##_print}; \
}

DEFINE_ATOM(int, int, a > b, "%d")
DEFINE_ATOM(str, char *, strmp(a, b) > 0, "%d")

/*
# 1
    file_in - program will read the data from this file
    file_out - program will write the data to this file
# 2
    array_length - number of elements in the generated array
    array_count - number of generated array
# options
    -r --reserve - reverse the sorting direction (form ascending to descending)
    -k --key - which field to use as a sorting key
    -s --sort - what sorting algorithm to use
*/

typedef struct Options {
    char *file_in;
    char *file_out;

    size_t array_length;
    size_t array_count;

    int reserve;
    size_t atom_index;
    sort_id sort;
} Options;


#define VECTOR_ITEM void
#define VECTOR_ITEM_DESTRUCTOR(item) do { \
    for (size_t i = index; i < vec->length; i++) \
        VECTOR_ITEM_DESTRUCTOR(get_item(vec, i)); \
    free(item); \
} while (0)

#include "vector.h"

typedef struct MultiArray {
    Vector vector;
    size_t *offsets;
    int (*greater)(void *a, void *b);
    size_t row_count;
} MultiArray;

int create_multi_array(MultiArray *mar, size_t capacity, size_t row_count) {
    mar = malloc(sizeof(MultiArray));
    if (mar == NULL) return -1;

    if (create(&mar->vector, capacity)) return -1;

    data = malloc(row_count * sizeof(VECTOR_ITEM));
    if (capacity && data == NULL) return -1;

    return 0;
}
