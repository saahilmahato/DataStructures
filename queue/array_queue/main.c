#include <stdio.h>
#include "../../test/test.h"
#include "array_queue.h"

int main(void) {
    printf("Testing Array-Based Queue Implementation\n");
    printf("============================================\n\n");

    test_reset();

    // Test 1: create_queue basic creation
    {
        printf("Test 1: create_queue basic creation\n");
        Queue *q = create_queue();
        assert_not_null(q);
        assert_not_null(q->array);
        assert_equal_size_t((size_t)INITIAL_CAPACITY, q->capacity);
        assert_equal_size_t((size_t)0, q->front);
        assert_equal_size_t((size_t)0, q->rear);
        assert_equal_size_t((size_t)0, q->size);
        assert_true(is_empty(q));
        assert_false(is_full(q));
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

    // Test 3: enqueue single element
    {
        printf("Test 3: enqueue single element\n");
        Queue *q = create_queue();
        assert_true(enqueue(q, 42));
        assert_equal_size_t((size_t)1, size(q));
        assert_false(is_empty(q));
        assert_false(is_full(q));

        int value;
        assert_true(front(q, &value));
        assert_equal_int(42, value);

        delete_queue(&q);
        printf("\n");
    }

    // Test 4: enqueue multiple elements (no wrap-around)
    {
        printf("Test 4: enqueue multiple elements (no wrap-around)\n");
        Queue *q = create_queue();
        for (int i = 1; i <= 5; ++i)
            assert_true(enqueue(q, i * 10));

        assert_equal_size_t((size_t)5, size(q));
        int value;
        assert_true(front(q, &value));
        assert_equal_int(10, value);

        delete_queue(&q);
        printf("\n");
    }

    // Test 5: dequeue single element
    {
        printf("Test 5: dequeue single element\n");
        Queue *q = create_queue();
        enqueue(q, 100);

        int value;
        assert_true(dequeue(q, &value));
        assert_equal_int(100, value);
        assert_equal_size_t((size_t)0, size(q));
        assert_true(is_empty(q));

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

        assert_true(dequeue(q, NULL)); // out_value NULL allowed
        assert_equal_size_t((size_t)0, size(q));

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
        assert_equal_size_t((size_t)2, size(q)); // still 2

        assert_true(front(q, NULL)); // out_value NULL allowed
        assert_equal_size_t((size_t)2, size(q));

        delete_queue(&q);
        printf("\n");
    }

    // Test 8: is_empty and is_full basic checks
    {
        printf("Test 8: is_empty and is_full basic checks\n");
        Queue *q = create_queue();
        assert_true(is_empty(q));
        assert_false(is_full(q));

        for (size_t i = 0; i < INITIAL_CAPACITY; ++i)
            assert_true(enqueue(q, (int)i));

        assert_false(is_empty(q));
        assert_true(is_full(q));

        delete_queue(&q);
        printf("\n");
    }

    // Test 9: resize_queue triggers on full
    {
        printf("Test 9: resize_queue triggers on full\n");
        Queue *q = create_queue();

        // Fill to capacity
        for (size_t i = 0; i < INITIAL_CAPACITY; ++i)
            assert_true(enqueue(q, (int)i));

        size_t old_capacity = q->capacity;
        assert_true(is_full(q));

        // This should trigger resize
        assert_true(enqueue(q, 9999));
        assert_false(is_full(q));
        assert_equal_size_t(old_capacity * GROWTH_FACTOR, q->capacity);
        assert_equal_size_t((size_t)INITIAL_CAPACITY + 1, size(q));

        int value;
        assert_true(front(q, &value));
        assert_equal_int(0, value); // FIFO preserved

        delete_queue(&q);
        printf("\n");
    }

    // Test 10: circular behavior with wrap-around
    {
        printf("Test 10: circular behavior with wrap-around\n");
        Queue *q = create_queue();

        // Fill completely
        for (int i = 1; i <= INITIAL_CAPACITY; ++i)
            enqueue(q, i);

        // Dequeue half to make rear wrap
        for (int i = 0; i < INITIAL_CAPACITY / 2; ++i)
            dequeue(q, NULL);

        // Enqueue more to wrap rear past capacity
        for (int i = 100; i < 110; ++i)
            assert_true(enqueue(q, i));

        // Front should still be correct
        int value;
        assert_true(front(q, &value));
        assert_equal_int((INITIAL_CAPACITY / 2) + 1, value);

        delete_queue(&q);
        printf("\n");
    }

    // Test 11: dequeue and front on empty queue
    {
        printf("Test 11: dequeue and front on empty queue\n");
        Queue *q = create_queue();
        int dummy;
        assert_false(dequeue(q, &dummy));
        assert_false(front(q, &dummy));
        assert_true(is_empty(q));
        delete_queue(&q);
        printf("\n");
    }

    // Test 12: enqueue/dequeue on NULL queue
    {
        printf("Test 12: enqueue/dequeue on NULL queue\n");
        Queue *q = NULL;
        assert_false(enqueue(q, 42));
        int dummy;
        assert_false(dequeue(q, &dummy));
        assert_false(front(q, &dummy));
        assert_true(is_empty(q));
        assert_equal_size_t((size_t)0, size(q));
        printf("\n");
    }

    // Test 13: Full lifecycle with resize and wrap-around
    {
        printf("Test 13: Full lifecycle with resize and wrap-around\n");
        Queue *q = create_queue();

        // Enqueue until resize
        for (int i = 0; i < INITIAL_CAPACITY + 5; ++i)
            assert_true(enqueue(q, i));

        // Dequeue some
        int val;
        for (int i = 0; i < 3; ++i) {
            assert_true(dequeue(q, &val));
            assert_equal_int(i, val);
        }

        // Enqueue more (now with wrap-around)
        for (int i = 1000; i < 1010; ++i)
            assert_true(enqueue(q, i));

        // Verify front is correct
        assert_true(front(q, &val));
        assert_equal_int(3, val);

        assert_equal_size_t((size_t)INITIAL_CAPACITY + 5 - 3 + 10, size(q));

        delete_queue(&q);
        printf("\n");
    }

    test_summary();

    return tests_failed;
}
