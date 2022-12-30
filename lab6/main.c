#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena.c"
#include "char_list.h"

#define MAX_LINE_LENGTH ARENA_SIZE / 2

bool read_line(CharNodeArena *arena, CharList *list) {
    CharNode *tail = NULL;
    list->head = NULL;

    char value;
    for (size_t i = 0; i < MAX_LINE_LENGTH; i++) {
        value = getchar();
        if (value == '\n' || value == EOF) return value == EOF;

        CharNode *cur = node_malloc(arena);
        cur->value = value;

        if (tail == NULL) list->head = cur;
        link(tail, cur);
        tail = cur;
    }

    while (!(value == '\n' || value == EOF)) value = getchar();
    return false;
}

void remove_excess_spaces(CharList *list) {
    CharNode *word = node_span(list->head, " \t");
    list->head = word;
    link(NULL, list->head);

    CharNode *space;
    while ((space = node_anti_span(word, " \t")) != NULL) {
        if ((word = node_span(space, " \t")) == NULL) {
            link(space->prev, NULL);
            break;
        }
        space->value = ' ';
        link(space, word);
    }
}

void dup_all_vowels(CharNodeArena *arena, CharList *list) {
    const char vowels[] =
        "aeiou"
        "AEIOU"
        "ауоиэыяюеё"
        "АУОИЭЫЯЮЕЁ";

    ITERATE_NODES(node, list->head) {
        bool vowel = false;
        for (const char *c = vowels; *c != '\0'; c++)
            if (node->value == *c) {
                vowel = true;
                break;
            }

        if (vowel) {
            CharNode *dup = node_malloc(arena);
            dup->value = node->value;
            link(node->prev, dup);
            link(dup, node);
        }
    }

    update_head(list);
}

#define PRINT_NODES(prefix, nodes, suffix) \
    printf(prefix);                        \
    print_nodes(nodes);                    \
    printf(suffix)

int main() {
    CharList list;
    CharNodeArena arena;

    while (1) {
        initialize_char_arena(&arena);

        printf(">>> ");
        if (read_line(&arena, &list)) {
            printf("Encountered EOF while reading a line, exiting ...\n");
            break;
        }
        PRINT_NODES("Input: \"", list.head, "\"\n");

        remove_excess_spaces(&list);
        dup_all_vowels(&arena, &list);
        PRINT_NODES("Output: \"", list.head, "\"\n");
    }
}
