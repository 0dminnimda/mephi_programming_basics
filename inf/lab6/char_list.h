#ifndef CHAR_LIST_H
#define CHAR_LIST_H

typedef struct CharNode {
    char value;
    struct CharNode *next;
    struct CharNode *prev;
} CharNode;

typedef struct {
    CharNode *head;
} CharList;

#define ITERATE_NODES(node, head) \
    for (CharNode *node = head; node != NULL; node = node->next)

void update_head(CharList *list);
void link(CharNode *a, CharNode *b);
void print_nodes(CharNode *start);
CharNode *node_span(CharNode *start, char *allowed);
CharNode *node_anti_span(CharNode *start, char *disallowed);

#endif  // CHAR_LIST_H
