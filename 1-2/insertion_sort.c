#include "list.h"
#include "insertion_sort.h"

void insertionsort(void *priv, struct list_head *head, list_cmp_func_t cmp)
{
    if (!head || list_empty(head))
        return;
        
    struct list_head *cur = head->next, *next = cur->next, **ptr = &head;
    
    for(; next != head; next = cur->next){
        if (cmp(priv, cur, next) > 0){
            do {
                if (cmp(priv, *ptr, next) > 0) 
                    list_move(next, (*ptr)->prev);
                else
                    ptr = &(*ptr)->next;
            } while(*ptr != next);
            ptr = &head;
        } else 
            cur = next;
        
    }
}