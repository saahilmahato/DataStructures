#include <stdio.h>
#include "../../test/test.h"
#include "tree.h"

int main(void) {
    printf("Testing Binary Tree Implementation\n");
    printf("============================================\n\n");

    test_reset();

    // Test 1: create_tree basic creation
    {
        printf("Test 1: create_tree basic creation\n");
        TreeNode *root = create_tree();
        assert_not_null(root);
        assert_null(root->left);
        assert_null(root->right);
        delete_tree(&root);
        assert_null(root);
        printf("\n");
    }

    // Test 2: inorder_traversal on NULL tree
    {
        printf("Test 2: inorder_traversal on NULL tree\n");
        inorder_traversal(NULL);
        printf(" (no output expected)\n");
        printf("\n");
    }

    // Test 3: preorder_traversal on NULL tree
    {
        printf("Test 3: preorder_traversal on NULL tree\n");
        preorder_traversal(NULL);
        printf(" (no output expected)\n");
        printf("\n");
    }

    // Test 4: postorder_traversal on NULL tree
    {
        printf("Test 4: postorder_traversal on NULL tree\n");
        postorder_traversal(NULL);
        printf(" (no output expected)\n");
        printf("\n");
    }

    // Test 5: Single node traversals
    {
        printf("Test 5: Single node traversals\n");
        TreeNode *root = create_tree();
        root->data = 42;

        printf("Inorder:   ");
        inorder_traversal(root);
        printf("  (expected: 42)\n");

        printf("Preorder:  ");
        preorder_traversal(root);
        printf("  (expected: 42)\n");

        printf("Postorder: ");
        postorder_traversal(root);
        printf("  (expected: 42)\n");

        delete_tree(&root);
        printf("\n");
    }

    // Test 6: Small tree - left child only
    {
        printf("Test 6: Small tree - left child only\n");
        TreeNode *root = create_tree();
        root->data = 1;
        root->left = create_tree();
        root->left->data = 2;
        root->right = NULL;

        printf("Inorder:   ");
        inorder_traversal(root);
        printf("  (expected: 21)\n");

        printf("Preorder:  ");
        preorder_traversal(root);
        printf("  (expected: 12)\n");

        printf("Postorder: ");
        postorder_traversal(root);
        printf("  (expected: 21)\n");

        delete_tree(&root);
        printf("\n");
    }

    // Test 7: Small tree - right child only
    {
        printf("Test 7: Small tree - right child only\n");
        TreeNode *root = create_tree();
        root->data = 1;
        root->right = create_tree();
        root->right->data = 3;
        root->left = NULL;

        printf("Inorder:   ");
        inorder_traversal(root);
        printf("  (expected: 13)\n");

        printf("Preorder:  ");
        preorder_traversal(root);
        printf("  (expected: 13)\n");

        printf("Postorder: ");
        postorder_traversal(root);
        printf("  (expected: 31)\n");

        delete_tree(&root);
        printf("\n");
    }

    // Test 8: Balanced tree with three levels
    {
        printf("Test 8: Balanced tree with three levels\n");
        /*
                  1
                /   \
               2     3
              / \   / \
             4   5 6   7
        */

        TreeNode *root = create_tree();
        root->data = 1;

        root->left = create_tree();
        root->left->data = 2;
        root->right = create_tree();
        root->right->data = 3;

        root->left->left = create_tree();
        root->left->left->data = 4;
        root->left->right = create_tree();
        root->left->right->data = 5;

        root->right->left = create_tree();
        root->right->left->data = 6;
        root->right->right = create_tree();
        root->right->right->data = 7;

        printf("Inorder:   ");
        inorder_traversal(root);
        printf("  (expected: 4251637)\n");

        printf("Preorder:  ");
        preorder_traversal(root);
        printf("  (expected: 1245367)\n");

        printf("Postorder: ");
        postorder_traversal(root);
        printf("  (expected: 4526731)\n");

        delete_tree(&root);
        printf("\n");
    }

    // Test 9: Skewed tree (right-skewed)
    {
        printf("Test 9: Skewed tree (right-skewed)\n");
        TreeNode *root = create_tree();
        root->data = 1;
        root->left = NULL;

        TreeNode *current = root;
        for (int i = 2; i <= 4; ++i) {
            current->right = create_tree();
            current = current->right;
            current->data = i;
        }

        printf("Inorder:   ");
        inorder_traversal(root);
        printf("  (expected: 1234)\n");

        printf("Preorder:  ");
        preorder_traversal(root);
        printf("  (expected: 1234)\n");

        printf("Postorder: ");
        postorder_traversal(root);
        printf("  (expected: 4321)\n");

        delete_tree(&root);
        printf("\n");
    }

    // Test 10: Complex tree with mixed structure
    {
        printf("Test 10: Complex tree with mixed structure\n");
        TreeNode *root = create_tree();
        root->data = 10;

        root->left = create_tree();
        root->left->data = 5;
        root->left->left = create_tree();
        root->left->left->data = 3;
        root->left->right = NULL;

        root->right = create_tree();
        root->right->data = 15;
        root->right->left = create_tree();
        root->right->left->data = 12;
        root->right->left->left = create_tree();
        root->right->left->left->data = 11;

        root->right->right = create_tree();
        root->right->right->data = 20;

        printf("Inorder:   ");
        inorder_traversal(root);
        printf("  (expected: 351011122015)\n");

        printf("Preorder:  ");
        preorder_traversal(root);
        printf("  (expected: 105312111520)\n");

        printf("Postorder: ");
        postorder_traversal(root);
        printf("  (expected: 351112201510)\n");

        delete_tree(&root);
        printf("\n");
    }

    test_summary();

    return tests_failed;
}
