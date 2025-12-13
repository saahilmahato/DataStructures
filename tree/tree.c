#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

TreeNode *create_tree(void) {
    TreeNode *root = malloc(sizeof(*root));
    if (!root)
        return nullptr;

    return root;
}

void inorder_traversal(TreeNode *root) {
    if (!root)
        return;

    inorder_traversal(root->left);
    printf("%d", root->data);
    inorder_traversal(root->right);
}

void preorder_traversal(TreeNode *root) {
    if (!root)
        return;

    printf("%d", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void postorder_traversal(TreeNode *root) {
    if (!root)
        return;

    postOrder_traversal(root->left);
    postOrder_traversal(root->right);
    printf("%d", root->data);
}
