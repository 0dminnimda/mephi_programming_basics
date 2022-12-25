#ifndef VECTOR_H_
#define VECTOR_H_

#ifndef VECTOR_ITEM
#error You should define 'VECTOR_ITEM' for Vector to work
#endif  // VECTOR_ITEM

#ifndef VECTOR_ITEM_DESTRUCTOR
#define VECTOR_ITEM_DESTRUCTOR(item)
#endif  // VECTOR_ITEM_DESTRUCTOR

#ifndef VECTOR_PRINT_ERROR
#define VECTOR_PRINT_ERROR(message)
#endif  // VECTOR_PRINT_ERRORS

typedef struct VectorNode_ *Vector;

#include <stdlib.h>

typedef struct VectorNode_ {
    VECTOR_ITEM *data;
    size_t capacity;
    size_t length;
} VectorNode_;

static inline void swap_vectors(Vector a, Vector b) {
    VectorNode_ tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline VECTOR_ITEM vec_get(Vector vec, size_t index) {
    return vec->data[index];
}

static inline void vec_set(Vector vec, size_t index, VECTOR_ITEM value) {
    vec->data[index] = value;
}

static inline VECTOR_ITEM *vec_data(Vector vec) { return vec->data; }

static inline size_t vec_capacity(Vector vec) { return vec->capacity; }

static inline size_t vec_length(Vector vec) { return vec->length; }

static inline int create_vector(Vector *vec, size_t capacity) {
    *vec = malloc(sizeof(VectorNode_));
    if (*vec == NULL) {
        VECTOR_PRINT_ERROR("Vector wasn't able to allocate new memory");
        return -1;
    }

    VECTOR_ITEM *data = malloc(capacity * sizeof(VECTOR_ITEM));
    if (capacity && data == NULL) {
        VECTOR_PRINT_ERROR("Vector wasn't able to allocate new memory");
        return -1;
    }

    (*vec)->data = data;
    (*vec)->capacity = capacity;
    (*vec)->length = 0;

    return 0;
}

static inline void vec_clear_starting_from(Vector vec, size_t index) {
    for (size_t i = index; i < vec->length; i++)
        VECTOR_ITEM_DESTRUCTOR(vec_get(vec, i));
    if (vec->length > index) vec->length = index;
}

static inline void vec_clear(Vector vec) { vec_clear_starting_from(vec, 0); }

static inline void vec_destroy_reference(Vector vec) {
    if (vec) free(vec->data);
    free(vec);
}

static inline void destroy_vector(Vector vec) {
    if (vec && vec->data) vec_clear(vec);
    vec_destroy_reference(vec);
}

static inline int vec_resize(Vector vec, size_t capacity) {
    vec_clear_starting_from(vec, capacity);
    vec->capacity = capacity;

    VECTOR_ITEM *data = realloc(vec->data, capacity * sizeof(VECTOR_ITEM));
    if (capacity && data == NULL) {
        VECTOR_PRINT_ERROR("Vector wasn't able to reallocate its memory");
        return -1;
    }

    vec->data = data;

    return 0;
}

static inline int vec_reserve(Vector vec, size_t capacity) {
    if (capacity <= vec->capacity) return 0;

    return vec_resize(vec, capacity);
}

static inline int vec_push_back(Vector vec, VECTOR_ITEM value) {
    if (vec->capacity == vec->length)
        if (vec_reserve(vec, vec->capacity * 2 + 1)) return -1;

    vec_set(vec, vec->length, value);
    vec->length++;

    return 0;
}

static inline void vec_pop_back(Vector vec) {
    vec_clear_starting_from(vec, vec->length - 1);
}

#endif  // VECTOR_H_
