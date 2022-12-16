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

static inline VECTOR_ITEM get_item(Vector vec, size_t index) {
    return vec->data[index];
}

static inline void set_item(Vector vec, size_t index, VECTOR_ITEM value) {
    vec->data[index] = value;
}

static inline size_t get_capacity(Vector vec) { return vec->capacity; }

static inline size_t get_length(Vector vec) { return vec->length; }

static inline int create(Vector *vec, size_t capacity) {
    *vec = malloc(sizeof(VectorNode_));
    if (*vec == NULL) {
        VECTOR_PRINT_ERROR("ERROR: Vector wasn't able to allocate new memory\n");
        return -1;
    }

    VECTOR_ITEM *data = malloc(capacity * sizeof(VECTOR_ITEM));
    if (capacity && data == NULL) {
        VECTOR_PRINT_ERROR("ERROR: Vector wasn't able to allocate new memory\n");
        return -1;
    }

    (*vec)->data = data;
    (*vec)->capacity = capacity;
    (*vec)->length = 0;

    return 0;
}

static inline void clear_vector_starting_from(Vector vec, size_t index) {
    for (size_t i = index; i < vec->length; i++)
        VECTOR_ITEM_DESTRUCTOR(get_item(vec, i));
    if (vec->length > index) vec->length = index;
}

static inline void clear_vector(Vector vec) { clear_vector_starting_from(vec, 0); }

static inline void destroy_reference(Vector vec) {
    if (vec)
        free(vec->data);
    free(vec);
}

static inline void destroy_vector(Vector vec) {
    if (vec && vec->data)
        clear_vector(vec);
    destroy_reference(vec);
}

static inline int resize(Vector vec, size_t capacity) {
    clear_vector_starting_from(vec, capacity);
    vec->capacity = capacity;

    VECTOR_ITEM *data = realloc(vec->data, capacity * sizeof(VECTOR_ITEM));
    if (capacity && data == NULL) {
        VECTOR_PRINT_ERROR("ERROR: Vector wasn't able to reallocate its memory\n");
        return -1;
    }

    vec->data = data;

    return 0;
}

static inline int reserve(Vector vec, size_t capacity) {
    if (capacity <= vec->capacity) return 0;

    return resize(vec, capacity);
}

static inline int push_back(Vector vec, VECTOR_ITEM value) {
    if (vec->capacity == vec->length)
        if (reserve(vec, vec->capacity * 2 + 1)) return -1;

    set_item(vec, vec->length, value);
    vec->length++;

    return 0;
}

static inline void pop_back(Vector vec) {
    clear_vector_starting_from(vec, vec->length - 1);
}

#endif  // VECTOR_H_
