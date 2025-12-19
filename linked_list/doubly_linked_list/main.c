#include <stdio.h>
#include "../../test/test.h"
#include "doubly_linked_list.h"

int main(void) {
    printf("Testing Doubly Linked List Implementation\n");
    printf("============================================\n\n");

    test_reset();

    // Test 1: get_length on NULL list
    {
        printf("Test 1: get_length on NULL list\n");
        ListNode const *head = NULL;
        assert_equal_size_t((size_t)0, get_length(head));
        printf("\n");
    }

    // Test 2: insert_first on empty list
    {
        printf("Test 2: insert_first on empty list\n");
        ListNode *head = NULL;
        assert_true(insert_first(&head, 42));
        assert_not_null(head);
        assert_equal_int(42, head->data);
        assert_null(head->prev);
        assert_null(head->next);
        assert_equal_size_t((size_t)1, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 3: insert_first multiple elements
    {
        printf("Test 3: insert_first multiple elements\n");
        ListNode *head = NULL;
        assert_true(insert_first(&head, 30));
        assert_true(insert_first(&head, 20));
        assert_true(insert_first(&head, 10));
        assert_equal_int(10, head->data);
        assert_null(head->prev);
        assert_equal_int(20, head->next->data);
        assert_equal_ptr(head, head->next->prev);
        assert_equal_int(30, head->next->next->data);
        assert_equal_ptr(head->next, head->next->next->prev);
        assert_null(head->next->next->next);
        assert_equal_size_t((size_t)3, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 4: insert_last on empty list
    {
        printf("Test 4: insert_last on empty list\n");
        ListNode *head = NULL;
        assert_true(insert_last(&head, 7));
        assert_not_null(head);
        assert_equal_int(7, head->data);
        assert_null(head->prev);
        assert_null(head->next);
        assert_equal_size_t((size_t)1, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 5: insert_last multiple elements
    {
        printf("Test 5: insert_last multiple elements\n");
        ListNode *head = NULL;
        assert_true(insert_last(&head, 10));
        assert_true(insert_last(&head, 20));
        assert_true(insert_last(&head, 30));
        assert_equal_int(10, head->data);
        assert_null(head->prev);
        assert_equal_int(20, head->next->data);
        assert_equal_ptr(head, head->next->prev);
        assert_equal_int(30, head->next->next->data);
        assert_equal_ptr(head->next, head->next->next->prev);
        assert_null(head->next->next->next);
        assert_equal_size_t((size_t)3, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 6: insert_at_position at position 0 (same as insert_first)
    {
        printf("Test 6: insert_at_position at position 0\n");
        ListNode *head = NULL;
        assert_true(insert_at_position(&head, 999, 0));
        assert_equal_int(999, head->data);
        assert_null(head->prev);
        assert_null(head->next);
        assert_equal_size_t((size_t)1, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 7: insert_at_position in middle and at end
    {
        printf("Test 7: insert_at_position in middle and at end\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_last(&head, 30);

        assert_true(insert_at_position(&head, 15, 1)); // middle
        assert_true(insert_at_position(&head, 40, 4)); // end

        assert_equal_int(10, head->data);
        assert_equal_int(15, head->next->data);
        assert_equal_int(20, head->next->next->data);
        assert_equal_int(30, head->next->next->next->data);
        assert_equal_int(40, head->next->next->next->next->data);

        // Check prev pointers
        assert_null(head->prev);
        assert_equal_ptr(head, head->next->prev);
        assert_equal_ptr(head->next, head->next->next->prev);
        assert_equal_ptr(head->next->next, head->next->next->next->prev);
        assert_equal_ptr(head->next->next->next, head->next->next->next->next->prev);

        assert_equal_size_t((size_t)5, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 8: insert_at_position invalid position
    {
        printf("Test 8: insert_at_position invalid position\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        assert_false(insert_at_position(&head, 20, 10));
        assert_equal_size_t((size_t)1, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 9: insert_at_position on NULL list (non-zero position)
    {
        printf("Test 9: insert_at_position on NULL list (non-zero position)\n");
        ListNode *head = NULL;
        assert_false(insert_at_position(&head, 10, 1));
        assert_null(head);
        printf("\n");
    }

    // Test 10: delete_first on single element
    {
        printf("Test 10: delete_first on single element\n");
        ListNode *head = NULL;
        insert_first(&head, 100);
        assert_true(delete_first(&head));
        assert_null(head);
        printf("\n");
    }

    // Test 11: delete_first on multiple elements
    {
        printf("Test 11: delete_first on multiple elements\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_last(&head, 30);
        assert_true(delete_first(&head));
        assert_equal_int(20, head->data);
        assert_null(head->prev);
        assert_equal_size_t((size_t)2, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 12: delete_first on NULL list
    {
        printf("Test 12: delete_first on NULL list\n");
        ListNode *head = NULL;
        assert_false(delete_first(&head));
        assert_null(head);
        printf("\n");
    }

    // Test 13: delete_last on single element
    {
        printf("Test 13: delete_last on single element\n");
        ListNode *head = NULL;
        insert_last(&head, 50);
        assert_true(delete_last(&head));
        assert_null(head);
        printf("\n");
    }

    // Test 14: delete_last on multiple elements
    {
        printf("Test 14: delete_last on multiple elements\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_last(&head, 30);
        assert_true(delete_last(&head));
        assert_equal_int(20, head->next->data);
        assert_null(head->next->next);
        assert_equal_size_t((size_t)2, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 15: delete_last on NULL list
    {
        printf("Test 15: delete_last on NULL list\n");
        ListNode *head = NULL;
        assert_false(delete_last(&head));
        assert_null(head);
        printf("\n");
    }

    // Test 16: delete_from_position at position 0
    {
        printf("Test 16: delete_from_position at position 0\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_last(&head, 30);
        assert_true(delete_from_position(&head, 0));
        assert_equal_int(20, head->data);
        assert_null(head->prev);
        assert_equal_size_t((size_t)2, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 17: delete_from_position in middle
    {
        printf("Test 17: delete_from_position in middle\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_last(&head, 30);
        assert_true(delete_from_position(&head, 1));
        assert_equal_int(10, head->data);
        assert_equal_int(30, head->next->data);
        assert_equal_ptr(head, head->next->prev);
        assert_null(head->next->next);
        assert_equal_size_t((size_t)2, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 18: delete_from_position invalid position
    {
        printf("Test 18: delete_from_position invalid position\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        assert_false(delete_from_position(&head, 5));
        assert_equal_size_t((size_t)1, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 19: delete_from_position on NULL list
    {
        printf("Test 19: delete_from_position on NULL list\n");
        ListNode *head = NULL;
        assert_false(delete_from_position(&head, 0));
        assert_null(head);
        printf("\n");
    }

    // Test 20: delete_list on populated list
    {
        printf("Test 20: delete_list on populated list\n");
        ListNode *head = NULL;
        insert_last(&head, 100);
        insert_last(&head, 200);
        insert_last(&head, 300);
        delete_list(&head);
        assert_null(head);
        printf("\n");
    }

    // Test 21: delete_list on NULL list
    {
        printf("Test 21: delete_list on NULL list\n");
        ListNode *head = NULL;
        delete_list(&head);
        assert_null(head);
        printf("\n");
    }

    // Test 22: Verify prev/next links after complex operations
    {
        printf("Test 22: Verify prev/next links after complex operations\n");
        ListNode *head = NULL;
        insert_first(&head, 30);
        insert_first(&head, 20);
        insert_last(&head, 40);
        insert_at_position(&head, 25, 1);

        // Expected: 20 <-> 25 <-> 30 <-> 40
        assert_equal_int(20, head->data);
        assert_equal_int(25, head->next->data);
        assert_equal_int(30, head->next->next->data);
        assert_equal_int(40, head->next->next->next->data);

        assert_null(head->prev);
        assert_equal_ptr(head, head->next->prev);
        assert_equal_ptr(head->next, head->next->next->prev);
        assert_equal_ptr(head->next->next, head->next->next->next->prev);
        assert_null(head->next->next->next->next);

        assert_equal_size_t((size_t)4, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    test_summary();

    return tests_failed;
}
