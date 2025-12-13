#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

TreeNode *createTree(void) {
    TreeNode *root = malloc(sizeof(*root));
    if (!root)
        return nullptr;

    return root;
}

void inorderTraversal(TreeNode *root) {
    if (!root)
        return;

    inorderTraversal(root->left);
    printf("%d", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(TreeNode *root) {
    if (!root)
        return;

    printf("%d", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postOrderTraversal(TreeNode *root) {
    if (!root)
        return;

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d", root->data);
}
