#include "binaryTree.h"
#include <time.h>

/* Assume each value is unique, check if two tree are same */
static bool checkTree(struct TreeNode *a, struct TreeNode *b)
{
    if (!a && !b)
        return true;
    
    if ((a && b) && (a->val == b->val))
        return checkTree(a->left, b->left) && checkTree(a->right, b->right);

    return false;
}

void FreeTree(struct TreeNode *root) 
{
    if (!root)
        return;
    
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

struct TreeNode *createNode(int val) 
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode *createTree(int depth, int value) {
    if (depth < 1)
        return NULL;
    struct TreeNode *root = createNode(value);
    root->left = createTree(depth - 1, value << 1);
    root->right = createTree(depth - 1, (value << 1) +1);
    
    return root;
}

void preorderTraversal(struct TreeNode *root, int treeArray[], int *index) {
    if (!root)
        return;
    
    treeArray[(*index)++] = root->val;
    preorderTraversal(root->left, treeArray, index);
    preorderTraversal(root->right, treeArray, index);
}

void inorderTraversal(struct TreeNode *root, int treeArray[], int *index) {
    if (!root)
        return;
    
    inorderTraversal(root->left, treeArray, index);
    treeArray[(*index)++] = root->val;
    inorderTraversal(root->right, treeArray, index);
}

int main() 
{
    int index = 0;
    int intiVal = 1;
    int depth = 15;
    struct TreeNode *root = createTree(depth, intiVal);

    // measure time
    clock_t start, end;
    clock_t total_time_used = 0;
    int test_time = 5;
    bool success = true;

    int preorder[treeSize(depth)], inorder[treeSize(depth)];
    
    index = 0;
    preorderTraversal(root, preorder, &index);

    index = 0;
    inorderTraversal(root, inorder, &index);
    
    // Now test our buildtree function
    for (int i=0; i<test_time; i++) {
        start = clock();
        struct TreeNode *test_root = buildTree(preorder, treeSize(depth), inorder, treeSize(depth));
        end = clock();
        if (!checkTree(root, test_root)) {
            printf("Check tree failed :(\n");
            success = false;
            break;
        }
        
        total_time_used += (end - start);
    }

    if (success)
        printf("elapsed avg time: %f\n", (double)(total_time_used) / CLOCKS_PER_SEC / test_time); 

    FreeTree(root);
    return 0;
}