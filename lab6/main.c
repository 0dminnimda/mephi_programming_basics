#include <stdio.h>
#include <stdlib.h>

#include "arena.c"
#include "char_list.h"

#define MAX_LINE_LENGTH ARENA_SIZE / 2

void read_line(CharNodeArena *arena, CharList *list) {
    CharNode *tail = NULL;
    list->head = NULL;

    for (size_t i = 0; i < MAX_LINE_LENGTH; i++) {
        char value = getchar();
        if (value == '\n' || value == EOF) break;

        CharNode *cur = node_malloc(arena);
        cur->value = value;

        if (tail == NULL)
            list->head = cur;
        else
            tail->next = cur;
        cur->prev = tail;
        tail = cur;
    }
}

void remove_excess_spaces(CharList *list) {
    CharNode *word = node_span(list->head, " \t");
    list->head = word;

    CharNode *space;
    while ((space = node_anti_span(word, " \t")) != NULL) {
        if ((word = node_span(space, " \t")) == NULL) {
            space->prev->next = NULL;
            break;
        }
        space->next = word;
        space->value = ' ';
    }
}

#define PRINT_NODES(prefix, nodes, suffix) \
    printf(prefix);                        \
    print_nodes(nodes);                    \
    printf(suffix)

int main() {
    CharList list;
    CharNodeArena arena;
    initialize_char_arena(&arena);

    read_line(&arena, &list);
    PRINT_NODES("Read: '", list.head, "'\n");

    PRINT_NODES("Word: '", node_span(list.head, " \t"), "'\n");
    PRINT_NODES("Space: '", node_anti_span(list.head, " \t"), "'\n");

    remove_excess_spaces(&list);
    PRINT_NODES("remove_excess_spaces: '", list.head, "'\n");
}
