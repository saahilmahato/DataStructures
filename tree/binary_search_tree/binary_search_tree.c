#include "binary_search_tree.h"
#include <stdlib.h>

TreeNode *create_tree(const int data) {
    TreeNode *root = malloc(sizeof(*root));
    if (!root) {
        return NULL;
    }

    root->data = data;
    root->left = NULL;
    root->right = NULL;

    return root;
}

bool insert_data(TreeNode **root, const int data) {
    if (root == NULL)
        return false;
    if (*root == NULL) {
        *root = create_tree(data);
        return *root != NULL;
    }

    if (data == (*root)->data)
        return false;

    if (data < (*root)->data)
        return insert_data(&(*root)->left, data);

    return insert_data(&(*root)->right, data);
}

bool delete_data(TreeNode **root, const int data) {
    if (root == NULL || *root == NULL)
        return false;

    if (data < (*root)->data)
        return delete_data(&(*root)->left, data);

    if (data > (*root)->data)
        return delete_data(&(*root)->right, data);

    TreeNode *to_delete = *root;

    if ((*root)->left == NULL) {
        *root = (*root)->right;
        free(to_delete);
    } else if ((*root)->right == NULL) {
        *root = (*root)->left;
        free(to_delete);
    } else {
        TreeNode **successor = &(*root)->right;
        while ((*successor)->left != NULL)
            successor = &(*successor)->left;

        (*root)->data = (*successor)->data;

        to_delete = *successor;
        *successor = (*successor)->right;
        free(to_delete);
    }

    return true;
}

bool contains_data(const TreeNode *root, const int data) {
    while (root != NULL) {
        if (root->data == data)
            return true;

        if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}

void delete_tree(TreeNode **root) {
    if (root == NULL || *root == NULL)
        return;

    delete_tree(&(*root)->left);
    delete_tree(&(*root)->right);

    free(*root);
    *root = NULL;
}
