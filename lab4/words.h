#define VECTOR_ITEM char *
#define VECTOR_ITEM_DESTRUCTOR(item) free(item)

#include "vector.h"

#define Words Vector

Words split(char *line);
void print_words(Words words);
