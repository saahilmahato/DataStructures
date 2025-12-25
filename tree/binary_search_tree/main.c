#include <stdio.h>
#include <string.h>
#include "../../test/test.h"
#include "binary_search_tree.h"

int main(void) {
    printf("Testing Binary Search Tree Implementation\n");
    printf("============================================\n\n");

    test_reset();

    // Test 1: create_tree basic
    {
        printf("Test 1: create_tree basic\n");
        TreeNode *root = create_tree(42);
        assert_not_null(root);
        assert_equal_int(42, root->data);
        assert_null(root->left);
        assert_null(root->right);
        delete_tree(&root);
        assert_null(root);
        printf("\n");
    }

    // Test 2: insert_data basic insertions
    {
        printf("Test 2: insert_data basic insertions\n");
        TreeNode *root = NULL;

        assert_true(insert_data(&root, 50));
        assert_true(insert_data(&root, 30));
        assert_true(insert_data(&root, 70));
        assert_true(insert_data(&root, 20));
        assert_true(insert_data(&root, 40));
        assert_true(insert_data(&root, 60));
        assert_true(insert_data(&root, 80));

        // Verify BST property by manual inorder walk
        // Expected order: 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> 80
        assert_true(contains_data(root, 20));
        assert_true(contains_data(root, 30));
        assert_true(contains_data(root, 40));
        assert_true(contains_data(root, 50));
        assert_true(contains_data(root, 60));
        assert_true(contains_data(root, 70));
        assert_true(contains_data(root, 80));

        assert_false(contains_data(root, 10));
        assert_false(contains_data(root, 55));
        assert_false(contains_data(root, 90));

        delete_tree(&root);
        printf("\n");
    }

    // Test 3: insert_data duplicate values
    {
        printf("Test 3: insert_data duplicate values\n");
        TreeNode *root = NULL;

        assert_true(insert_data(&root, 100));
        assert_false(insert_data(&root, 100)); // duplicate rejected

        assert_true(contains_data(root, 100));
        assert_false(contains_data(root, 50));

        delete_tree(&root);
        printf("\n");
    }

    // Test 4: contains_data basic
    {
        printf("Test 4: contains_data basic\n");
        TreeNode *root = NULL;

        insert_data(&root, 10);
        insert_data(&root, 5);
        insert_data(&root, 15);
        insert_data(&root, 12);
        insert_data(&root, 18);

        assert_true(contains_data(root, 10));
        assert_true(contains_data(root, 5));
        assert_true(contains_data(root, 15));
        assert_true(contains_data(root, 12));
        assert_true(contains_data(root, 18));

        assert_false(contains_data(root, 999));
        assert_false(contains_data(root, 0));
        assert_false(contains_data(root, 13));
        assert_false(contains_data(NULL, 10));

        delete_tree(&root);
        printf("\n");
    }

    // Test 5: delete_data leaf node
    {
        printf("Test 5: delete_data leaf node\n");
        TreeNode *root = NULL;

        insert_data(&root, 50);
        insert_data(&root, 30);
        insert_data(&root, 70);
        insert_data(&root, 20);

        assert_true(delete_data(&root, 20)); // leaf node

        assert_false(contains_data(root, 20));
        assert_true(contains_data(root, 30));
        assert_true(contains_data(root, 50));
        assert_true(contains_data(root, 70));

        delete_tree(&root);
        printf("\n");
    }

    // Test 6: delete_data node with one child
    {
        printf("Test 6: delete_data node with one child\n");
        TreeNode *root = NULL;

        insert_data(&root, 50);
        insert_data(&root, 30);
        insert_data(&root, 20); // leaf under 30

        assert_true(delete_data(&root, 30)); // 30 has one child (20)

        assert_true(contains_data(root, 20));
        assert_false(contains_data(root, 30));
        assert_true(contains_data(root, 50));

        delete_tree(&root);
        printf("\n");
    }

    // Test 7: delete_data node with two children (successor case)
    {
        printf("Test 7: delete_data node with two children\n");
        TreeNode *root = NULL;

        insert_data(&root, 50);
        insert_data(&root, 30);
        insert_data(&root, 70);
        insert_data(&root, 20);
        insert_data(&root, 40);
        insert_data(&root, 60);
        insert_data(&root, 80);

        // Root 50 has two children
        assert_true(delete_data(&root, 50));

        // Successor (60) should replace 50
        assert_equal_int(60, root->data);
        assert_false(contains_data(root, 50));
        assert_true(contains_data(root, 20));
        assert_true(contains_data(root, 30));
        assert_true(contains_data(root, 40));
        assert_true(contains_data(root, 70));
        assert_true(contains_data(root, 80));

        delete_tree(&root);
        printf("\n");
    }

    // Test 8: delete_data non-existing value
    {
        printf("Test 8: delete_data non-existing value\n");
        TreeNode *root = NULL;

        insert_data(&root, 100);

        assert_false(delete_data(&root, 999));
        assert_false(delete_data(&root, 0));
        assert_true(contains_data(root, 100));

        delete_tree(&root);
        printf("\n");
    }

    // Test 9: delete_data on empty tree
    {
        printf("Test 9: delete_data on empty tree\n");
        TreeNode *root = NULL;
        assert_false(delete_data(&root, 42));
        assert_null(root);
        printf("\n");
    }

    // Test 10: Complex lifecycle - multiple inserts and deletes
    {
        printf("Test 10: Complex lifecycle\n");
        TreeNode *root = NULL;

        assert_true(insert_data(&root, 100));
        assert_true(insert_data(&root, 50));
        assert_true(insert_data(&root, 150));
        assert_true(insert_data(&root, 25));
        assert_true(insert_data(&root, 75));
        assert_true(insert_data(&root, 125));
        assert_true(insert_data(&root, 175));

        // Verify all present
        assert_true(contains_data(root, 25));
        assert_true(contains_data(root, 50));
        assert_true(contains_data(root, 75));
        assert_true(contains_data(root, 100));
        assert_true(contains_data(root, 125));
        assert_true(contains_data(root, 150));
        assert_true(contains_data(root, 175));

        // Delete various cases
        assert_true(delete_data(&root, 25)); // leaf
        assert_true(delete_data(&root, 150)); // two children
        assert_true(delete_data(&root, 75)); // one child

        // Check remaining
        assert_false(contains_data(root, 25));
        assert_true(contains_data(root, 50));
        assert_false(contains_data(root, 75));
        assert_true(contains_data(root, 100));
        assert_true(contains_data(root, 125));
        assert_false(contains_data(root, 150));
        assert_true(contains_data(root, 175));

        delete_tree(&root);
        printf("\n");
    }

    test_summary();

    return tests_failed;
}
