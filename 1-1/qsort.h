#include <stdlib.h>

typedef struct __node {
    struct __node *left, *right;
    struct __node *next;
    long value;
} node_t;

void list_add(node_t **list, node_t *node_t);
node_t *list_tail(node_t **left);
int list_length(node_t **left);
node_t *list_construct(node_t *list, int n);
void list_free(node_t **list);
void quick_sort(node_t **list);