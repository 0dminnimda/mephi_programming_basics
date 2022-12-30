#include "char_list.h"

#define ARENA_SIZE 1024

typedef struct {
    CharNode items[ARENA_SIZE];
    size_t unoccupied;
} CharNodeArena;

CharNode *node_malloc(CharNodeArena *arena) {
    return &arena->items[arena->unoccupied++];
}

CharNode *safe_node_malloc(CharNodeArena *arena) {
    return arena->unoccupied < ARENA_SIZE ? node_malloc(arena) : NULL;
}
