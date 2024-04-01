#include "list.h"
#include "insertion_sort.h"

void insertionsort(void *priv, struct list_head *head, list_cmp_func_t cmp)
{
    if (!head || list_empty(head) || list_is_singular(head))
        return;
        
    struct list_head *cur = head->next, *next = cur->next, **ptr = &head->next;
    
    for(; next != head;){
        if (cmp(priv, cur, next) > 0){
            do {
                if (cmp(priv, *ptr, next) > 0) 
                    list_move(next, (*ptr)->prev);
                else
                    ptr = &(*ptr)->next;
            } while(*ptr != next);
            next = cur->next;
            ptr = &head->next;
        } else {
            cur = next;
            next = cur->next;
        }
    }
}