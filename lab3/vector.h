#include <stdlib.h>

typedef float vector_item_t;
// #ifndef CUSTOM_VECTOR_ITEM_TYPE
// typedef int vector_item_t;
// #else
// CUSTOM_VECTOR_ITEM_TYPE_DEF
// #endif

typedef struct VectorNode* Vector;

vector_item_t get_item(Vector vec, size_t index);
void set_item(Vector vec, size_t index, vector_item_t value);

size_t get_capacity(Vector vec);
size_t get_length(Vector vec);

int create(Vector *vec, size_t capacity);
void destroy(Vector vec);
int reserve(Vector vec, size_t capacity);

int push_back(Vector vec, vector_item_t value);
int insert(Vector vec, size_t index, vector_item_t value);
