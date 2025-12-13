#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createTree(void);

void inorderTraversal(TreeNode *root);

void preorderTraversal(TreeNode *root);

void postorderTraversal(TreeNode *root);

#endif
