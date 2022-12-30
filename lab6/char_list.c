#include "char_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void link(CharNode *a, CharNode *b) {
    if (a != NULL) a->next = b;
    if (b != NULL) b->prev = a;
}

void print_nodes(CharNode *start) {
    ITERATE_NODES(node, start) putchar(node->value);
}

CharNode *node_span(CharNode *start, char *allowed) {
    ITERATE_NODES(node, start) {
        bool ok = false;
        for (char *c = allowed; *c != '\0'; c++)
            if (node->value == *c) {
                ok = true;
                break;
            }

        if (!ok) return node;
    }
    return NULL;
}

CharNode *node_anti_span(CharNode *start, char *disallowed) {
    ITERATE_NODES(node, start) {
        for (char *c = disallowed; *c != '\0'; c++)
            if (node->value == *c) return node;
    }
    return NULL;
}
