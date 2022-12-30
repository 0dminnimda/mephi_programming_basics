#include "char_list.h"

#define ARENA_SIZE 1024

typedef struct {
    CharNode items[ARENA_SIZE];
    size_t unoccupied;
} CharNodeArena;

void initialize_char_arena(CharNodeArena *arena) {
    arena->unoccupied = 0;
    for (size_t i = 0; i < ARENA_SIZE; i++) {
        arena->items[i] = (CharNode){.value=(char)0, .next=NULL, .prev=NULL};
    }
}

CharNode *node_malloc(CharNodeArena *arena) {
    return &arena->items[arena->unoccupied++];
}

CharNode *safe_node_malloc(CharNodeArena *arena) {
    return arena->unoccupied < ARENA_SIZE ? node_malloc(arena) : NULL;
}
