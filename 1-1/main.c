#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "qsort.h"

/* Verify if list is order */
static bool list_is_ordered(struct list_head *head)
{       
    if (!head)
        return true;

    element_t *node, *safe;
    list_for_each_entry_safe(node, safe, head, list) {
        if (&safe->list == head) {
            printf("List is ordered\n");
            return true;
        }
        if (strcmp(node->value, safe->value) > 0) {
            printf("[Error] : %s is greater than %s\n", node->value, safe->value);
            return false;
        }
    }
    printf("List is ordered\n");
    return true;
}

/* shuffle array, only work if n < RAND_MAX */
void shuffle(int *array, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void show_head(struct list_head *head)
{
    element_t *node;
    
    list_for_each_entry(node, head, list){
        printf("%d", 1);
        printf("%s\n", node->value);
    }
}


int main(int argc, char **argv)
{
    struct list_head list;
    INIT_LIST_HEAD(&list);
    struct list_head *head = &list;

    size_t count = 100000;

    int *test_arr = malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i)
        test_arr[i] = i;
    
    shuffle(test_arr, count);

    while (count--)
        head = list_construct(head, test_arr[count]);

    quick_sort(head);
    assert(list_is_ordered(head));

    free(test_arr);

    return 0;
}