#ifndef VECTOR_H_
#define VECTOR_H_

#ifndef VECTOR_ITEM_TYPE
#error You should define 'VECTOR_ITEM_TYPE' for Vector to work
#endif  // VECTOR_ITEM_TYPE

typedef struct VectorNode_ *Vector;

#include <stdlib.h>

typedef struct VectorNode_ {
    VECTOR_ITEM_TYPE *data;
    size_t capacity;
    size_t length;
} VectorNode_;

inline VECTOR_ITEM_TYPE get_item(Vector vec, size_t index) {
    return vec->data[index];
}

inline void set_item(Vector vec, size_t index, VECTOR_ITEM_TYPE value) {
    vec->data[index] = value;
}

inline size_t get_capacity(Vector vec) { return vec->capacity; }

inline size_t get_length(Vector vec) { return vec->length; }

inline void reset_length(Vector vec) { vec->length = 0; }

inline int create(Vector *vec, size_t capacity) {
    *vec = malloc(sizeof(VectorNode_));
    if (*vec == NULL) return -1;

    VECTOR_ITEM_TYPE *data = malloc(capacity * sizeof(VECTOR_ITEM_TYPE));
    if (data == NULL) return -1;

    (*vec)->data = data;
    (*vec)->capacity = capacity;
    (*vec)->length = 0;

    return 0;
}

inline void destroy(Vector vec) {
    free(vec->data);
    free(vec);
}

inline int reserve(Vector vec, size_t capacity) {
    if (capacity <= vec->capacity) return 0;

    VECTOR_ITEM_TYPE *data =
        realloc(vec->data, capacity * sizeof(VECTOR_ITEM_TYPE));
    if (data == NULL) return -1;

    vec->data = data;
    vec->capacity = capacity;

    return 0;
}

inline int push_back(Vector vec, VECTOR_ITEM_TYPE value) {
    if (vec->capacity == vec->length)
        if (reserve(vec, vec->capacity * 2 + 1)) return -1;

    set_item(vec, vec->length, value);
    vec->length++;

    return 0;
}

inline void pop_back(Vector vec) {
    if (vec->length) vec->length--;
}

#endif // VECTOR_H_
