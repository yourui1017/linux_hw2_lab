#include "binaryTree.h"

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first)
        h->first->pprev = &n->next;
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

static int find(int num, int size, const struct hlist_head *heads)
{
    struct hlist_node *p;
    int hash = (num < 0 ? -num : num) % size;
    hlist_for_each (p, &heads[hash]) {
        struct order_node *on = container_of(p, struct order_node, node);
        if (num == on->val)
            return on->idx;
    }
    return -1;
}

static struct TreeNode *dfs(int *preorder,
                            int pre_low,
                            int pre_high,
                            int *inorder,
                            int in_low,
                            int in_high,
                            struct hlist_head *in_heads,
                            int size)
{
    if (in_low > in_high || pre_low > pre_high)
        return NULL;

    struct TreeNode *tn = malloc(sizeof(*tn));
    tn->val = preorder[pre_low];
    int idx = find(preorder[pre_low], size, in_heads);
    tn->left = dfs(preorder, pre_low + 1, pre_low + (idx - in_low), inorder,
                   in_low, idx - 1, in_heads, size);
    tn->right = dfs(preorder, pre_high - (in_high - idx - 1), pre_high, inorder,
                    idx + 1, in_high, in_heads, size);
    return tn;
}

static inline void node_add(int val,
                            int idx,
                            int size,
                            struct hlist_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->idx = idx;
    int hash = (val < 0 ? -val : val) % size;
    hlist_add_head(&on->node, &heads[hash]);
}

struct TreeNode *buildTree(int *preorder,
                                  int preorderSize,
                                  int *inorder,
                                  int inorderSize)
{
    struct hlist_head *in_heads = malloc(inorderSize * sizeof(*in_heads));
    for (int i = 0; i < inorderSize; i++)
        INIT_HLIST_HEAD(&in_heads[i]);
    for (int i = 0; i < inorderSize; i++)
        node_add(inorder[i], i, inorderSize, in_heads);

    return dfs(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1,
               in_heads, inorderSize);
}