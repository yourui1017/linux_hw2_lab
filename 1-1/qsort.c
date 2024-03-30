#include "qsort.h"

struct list_head *list_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head)
        return NULL;
    INIT_LIST_HEAD(head);
    return head;
}

struct list_head *list_tail(struct list_head *head)
{
    return head->prev;
}

int list_length(struct list_head *head)
{
    if (!head)
        return 0;

    int count = 0;
    struct list_head *node;

    list_for_each (node, head)
        count++;

    return count;
}


struct list_head *list_construct(struct list_head *head, int n)
{
    element_t *node = malloc(sizeof(element_t)); 
    list_add(&node->list, head);
    char buf[20];
    sprintf(buf, "%d", n);
    node->value = buf;
    return head;
}


void list_free(struct list_head *head)
{
    if (!head)
        return;

    element_t *safe, *node;
    list_for_each_entry_safe(node, safe, head, list) 
        free(node);

    free(head);
}

struct list_head *select_pivot(struct list_head *L){
    struct list_head *pivot = L->next;
    int listsize = list_length(L);
    int rnum = rand();
    for (int i = 0; i < (rnum % listsize); i++)
        pivot = pivot->next;
    return pivot;
}

void quick_sort(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
    int n = list_length(head);
    int i = 0;
    int max_level = 1 * n+1;
    struct list_head *begin[max_level];
    struct list_head *result = list_new(), *left = list_new(), *right = list_new();
    
    begin[0] = head;
    for(int i = 1; i < max_level; i++) {
        begin[i] = list_new();
    }

    while (i >= 0) {
        struct list_head *L = begin[i], *R = list_tail(begin[i]);
        if (L->next != R) {
            
            // struct list_head *pivot = L->next;
            // element_t *pivot_entry = list_entry(pivot, element_t, list);
            // list_del_init(pivot);

            struct list_head *pivot = select_pivot(L);
            element_t *pivot_entry = list_entry(pivot, element_t, list);
            list_del_init(pivot);

            element_t *entry, *safe;
            list_for_each_entry_safe(entry, safe, L, list){
                list_move(&entry->list, ((strcmp(entry->value, pivot_entry->value) > 0) ? right : left));
            }

            list_splice_init(left, begin[i]);
            list_add(pivot,begin[i + 1]);
            list_splice_init(right, begin[i+2]);

            i += 2;
        } else {
            if (!list_empty(L)) 
                list_move(L->next, result);
            i--;
        }
    }
    list_splice_init(result, head);
    free(result);

    for(int j=1 ; j<max_level ; j++){
        free(begin[j]);
    }
    free(right);
    free(left);
}