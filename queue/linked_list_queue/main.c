#include <stdio.h>
#include "../../test/test.h"
#include "linked_list_queue.h"

int main(void) {
    printf("Testing Linked List-Based Queue Implementation\n");
    printf("============================================\n\n");

    test_reset();

    // Test 1: create_queue basic creation
    {
        printf("Test 1: create_queue basic creation\n");
        Queue *q = create_queue();
        assert_not_null(q);
        assert_null(q->front);
        assert_null(q->rear);
        assert_equal_size_t((size_t)0, q->size);
        assert_true(is_empty(q));
        assert_equal_size_t((size_t)0, size(q));
        delete_queue(&q);
        assert_null(q);
        printf("\n");
    }

    // Test 2: delete_queue on NULL
    {
        printf("Test 2: delete_queue on NULL\n");
        Queue *q = NULL;
        delete_queue(&q);
        assert_null(q);
        printf("\n");
    }

    // Test 3: enqueue single element (empty to non-empty)
    {
        printf("Test 3: enqueue single element\n");
        Queue *q = create_queue();
        assert_true(enqueue(q, 42));
        assert_equal_size_t((size_t)1, size(q));
        assert_false(is_empty(q));
        assert_not_null(q->front);
        assert_not_null(q->rear);
        assert_equal_ptr(q->front, q->rear);
        assert_equal_int(42, q->front->data);

        int value;
        assert_true(front(q, &value));
        assert_equal_int(42, value);

        delete_queue(&q);
        printf("\n");
    }

    // Test 4: enqueue multiple elements
    {
        printf("Test 4: enqueue multiple elements\n");
        Queue *q = create_queue();
        assert_true(enqueue(q, 10));
        assert_true(enqueue(q, 20));
        assert_true(enqueue(q, 30));

        assert_equal_size_t((size_t)3, size(q));
        assert_equal_int(10, q->front->data);
        assert_equal_int(30, q->rear->data);
        assert_not_null(q->front->next);
        assert_not_null(q->front->next->next);
        assert_null(q->rear->next);

        delete_queue(&q);
        printf("\n");
    }

    // Test 5: dequeue single element (non-empty to empty)
    {
        printf("Test 5: dequeue single element\n");
        Queue *q = create_queue();
        enqueue(q, 100);

        int value;
        assert_true(dequeue(q, &value));
        assert_equal_int(100, value);
        assert_equal_size_t((size_t)0, size(q));
        assert_true(is_empty(q));
        assert_null(q->front);
        assert_null(q->rear);

        delete_queue(&q);
        printf("\n");
    }

    // Test 6: dequeue multiple elements
    {
        printf("Test 6: dequeue multiple elements\n");
        Queue *q = create_queue();
        enqueue(q, 10);
        enqueue(q, 20);
        enqueue(q, 30);

        int v1;
        int v2;
        assert_true(dequeue(q, &v1));
        assert_equal_int(10, v1);
        assert_equal_size_t((size_t)2, size(q));

        assert_true(dequeue(q, &v2));
        assert_equal_int(20, v2);
        assert_equal_size_t((size_t)1, size(q));

        assert_true(dequeue(q, NULL)); // out_value can be NULL
        assert_equal_size_t((size_t)0, size(q));
        assert_null(q->front);
        assert_null(q->rear);

        delete_queue(&q);
        printf("\n");
    }

    // Test 7: front without removing
    {
        printf("Test 7: front without removing\n");
        Queue *q = create_queue();
        enqueue(q, 55);
        enqueue(q, 66);

        int value;
        assert_true(front(q, &value));
        assert_equal_int(55, value);
        assert_equal_size_t((size_t)2, size(q)); // size unchanged

        assert_true(front(q, NULL));
        assert_equal_size_t((size_t)2, size(q));

        delete_queue(&q);
        printf("\n");
    }

    // Test 8: is_empty and size checks
    {
        printf("Test 8: is_empty and size checks\n");
        Queue *q = create_queue();
        assert_true(is_empty(q));
        assert_equal_size_t((size_t)0, size(q));

        enqueue(q, 1);
        enqueue(q, 2);
        assert_false(is_empty(q));
        assert_equal_size_t((size_t)2, size(q));

        dequeue(q, NULL);
        assert_equal_size_t((size_t)1, size(q));

        delete_queue(&q);
        printf("\n");
    }

    // Test 9: dequeue on empty queue
    {
        printf("Test 9: dequeue on empty queue\n");
        Queue *q = create_queue();
        int dummy;
        assert_false(dequeue(q, &dummy));
        assert_true(is_empty(q));
        assert_null(q->front);
        assert_null(q->rear);

        delete_queue(&q);
        printf("\n");
    }

    // Test 10: front on empty queue
    {
        printf("Test 10: front on empty queue\n");
        Queue *q = create_queue();
        int dummy;
        assert_false(front(q, &dummy));
        assert_true(is_empty(q));

        delete_queue(&q);
        printf("\n");
    }

    // Test 11: enqueue/dequeue/front on NULL queue
    {
        printf("Test 11: enqueue/dequeue/front on NULL queue\n");
        Queue *q = NULL;
        int dummy;

        assert_false(enqueue(q, 999));
        assert_false(dequeue(q, &dummy));
        assert_false(front(q, &dummy));
        assert_true(is_empty(q));
        assert_equal_size_t((size_t)0, size(q));

        printf("\n");
    }

    // Test 12: Full lifecycle - multiple operations
    {
        printf("Test 12: Full lifecycle - multiple operations\n");
        Queue *q = create_queue();

        assert_true(enqueue(q, 100));
        assert_true(enqueue(q, 200));
        assert_true(enqueue(q, 300));

        int val;
        assert_true(front(q, &val));
        assert_equal_int(100, val);

        assert_true(dequeue(q, &val));
        assert_equal_int(100, val);
        assert_equal_size_t((size_t)2, size(q));

        assert_true(enqueue(q, 400));
        assert_true(front(q, &val));
        assert_equal_int(200, val);

        assert_true(dequeue(q, NULL));
        assert_true(dequeue(q, NULL));
        assert_true(dequeue(q, NULL));
        assert_true(is_empty(q));

        delete_queue(&q);
        printf("\n");
    }

    // Test 13: Verify rear becomes NULL when queue empties
    {
        printf("Test 13: Verify rear becomes NULL when queue empties\n");
        Queue *q = create_queue();
        enqueue(q, 777);

        int dummy;
        assert_true(dequeue(q, &dummy));
        assert_null(q->front);
        assert_null(q->rear);
        assert_true(is_empty(q));

        delete_queue(&q);
        printf("\n");
    }

    test_summary();

    return tests_failed == 0 ? 0 : 1;
}
