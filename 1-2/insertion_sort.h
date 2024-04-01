
struct list_head;

typedef int (*list_cmp_func_t)(void *,
                               const struct list_head *,
                               const struct list_head *);

void insertionsort(void *priv, struct list_head *head, list_cmp_func_t cmp);