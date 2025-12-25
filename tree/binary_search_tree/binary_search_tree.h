#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_tree(int data);

bool insert_data(TreeNode **root, int data);

bool delete_data(TreeNode **root, int data);

bool contains_data(const TreeNode *root, int data);

void delete_tree(TreeNode **root);

#endif
