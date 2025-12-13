#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_tree(void);

void inorder_traversal(TreeNode *root);

void preorder_traversal(TreeNode *root);

void postorder_traversal(TreeNode *root);

#endif
