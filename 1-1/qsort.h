#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "random.h"
#include "list.h"

#define MIN_RANDSTR_LEN 5
#define CHAR_LEN 10

typedef int (*list_cmp_func_t)(void *, struct list_head *, struct list_head *);

static const char charset[] = "abcdefghijklmnopqrstuvwxyz";

typedef struct {
    char *value;
    struct list_head list;
} element_t;

struct list_head *list_new();
struct list_head *list_tail(struct list_head *);
int list_length(struct list_head *);
struct list_head *list_construct(struct list_head *list, int n);
void list_free(struct list_head *);
struct list_head *select_pivot(struct list_head *L);
void quick_sort(struct list_head *);