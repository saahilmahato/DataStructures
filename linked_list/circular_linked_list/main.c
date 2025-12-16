#include <stdio.h>
#include "../../test/test.h"
#include "circular_linked_list.h"

int main(void) {
    printf("Testing Circular Linked List Implementation\n");
    printf("============================================\n\n");

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
        assert_true(insert_first(&head, 10));
        assert_not_null(head);
        assert_equal_int(10, head->data);
        assert_equal_ptr(head, head->next);
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
        assert_equal_size_t((size_t)3, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 4: insert_last on empty list
    {
        printf("Test 4: insert_last on empty list\n");
        ListNode *head = NULL;
        assert_true(insert_last(&head, 10));
        assert_not_null(head);
        assert_equal_int(10, head->data);
        assert_equal_ptr(head, head->next);
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
        assert_equal_size_t((size_t)3, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 6: insert_at_position at position 0
    {
        printf("Test 6: insert_at_position at position 0\n");
        ListNode *head = NULL;
        assert_true(insert_at_position(&head, 10, 0));
        assert_not_null(head);
        assert_equal_int(10, head->data);
        assert_equal_size_t((size_t)1, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    // Test 7: insert_at_position in middle
    {
        printf("Test 7: insert_at_position in middle\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 30);
        assert_true(insert_at_position(&head, 20, 1));
        assert_equal_size_t((size_t)3, get_length(head));
        assert_equal_int(10, head->data);
        assert_equal_int(20, head->next->data);
        assert_equal_int(30, head->next->next->data);
        delete_list(&head);
        printf("\n");
    }

    // Test 8: insert_at_position invalid position
    {
        printf("Test 8: insert_at_position invalid position\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        assert_false(insert_at_position(&head, 20, 5));
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
        insert_first(&head, 10);
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
        insert_first(&head, 10);
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
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_last(&head, 30);
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

    // Test 22: Circular property verification
    {
        printf("Test 22: Circular property verification\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_last(&head, 30);

        ListNode *current = head;
        int count = 0;
        do {
            count++;
            current = current->next;
        } while (current != head && count < 10);

        assert_equal_ptr(head, current);
        assert_equal_int(3, count);
        delete_list(&head);
        printf("\n");
    }

    // Test 23: Complex operation sequence
    {
        printf("Test 23: Complex operation sequence\n");
        ListNode *head = NULL;
        insert_last(&head, 10);
        insert_last(&head, 20);
        insert_first(&head, 5);
        insert_at_position(&head, 15, 2);
        assert_equal_size_t((size_t)4, get_length(head));
        delete_from_position(&head, 1);
        assert_equal_size_t((size_t)3, get_length(head));
        delete_first(&head);
        delete_last(&head);
        assert_equal_size_t((size_t)1, get_length(head));
        delete_list(&head);
        printf("\n");
    }

    test_summary();
    return tests_failed;
}
