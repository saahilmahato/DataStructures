#include <stdio.h>
#include "../../test/test.h"
#include "array_stack.h"

int main(void) {
    printf("Testing Array-Based Stack Implementation\n");
    printf("============================================\n\n");

    test_reset();

    // Test 1: create_stack basic creation
    {
        printf("Test 1: create_stack basic creation\n");
        Stack *s = create_stack();
        assert_not_null(s);
        assert_not_null(s->array);
        assert_equal_int(-1, s->top);
        assert_equal_size_t((size_t)INITIAL_CAPACITY, s->capacity);
        assert_true(is_empty(s));
        assert_false(is_full(s));
        assert_equal_int(0, size(s));
        delete_stack(&s);
        assert_null(s);
        printf("\n");
    }

    // Test 2: delete_stack on NULL
    {
        printf("Test 2: delete_stack on NULL\n");
        Stack *s = NULL;
        delete_stack(&s);
        assert_null(s);
        printf("\n");
    }

    // Test 3: push single element
    {
        printf("Test 3: push single element\n");
        Stack *s = create_stack();
        assert_true(push(s, 42));
        assert_equal_int(0, s->top);
        assert_equal_int(42, s->array[0]);
        assert_false(is_empty(s));
        assert_equal_int(1, size(s));

        int value;
        assert_true(peek(s, &value));
        assert_equal_int(42, value);

        delete_stack(&s);
        printf("\n");
    }

    // Test 4: push multiple elements (no resize)
    {
        printf("Test 4: push multiple elements (no resize)\n");
        Stack *s = create_stack();
        for (int i = 1; i <= 5; ++i)
            assert_true(push(s, i * 10));

        assert_equal_int(4, s->top);
        assert_equal_int(50, s->array[4]);
        assert_equal_int(10, s->array[0]);
        assert_equal_int(5, size(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 5: pop single element
    {
        printf("Test 5: pop single element\n");
        Stack *s = create_stack();
        push(s, 100);

        int value;
        assert_true(pop(s, &value));
        assert_equal_int(100, value);
        assert_equal_int(-1, s->top);
        assert_true(is_empty(s));
        assert_equal_int(0, size(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 6: pop multiple elements
    {
        printf("Test 6: pop multiple elements\n");
        Stack *s = create_stack();
        push(s, 10);
        push(s, 20);
        push(s, 30);

        int v1;
        int v2;
        assert_true(pop(s, &v1));
        assert_equal_int(30, v1);
        assert_equal_int(1, s->top);
        assert_equal_int(2, size(s));

        assert_true(pop(s, &v2));
        assert_equal_int(20, v2);
        assert_equal_int(0, s->top);
        assert_equal_int(1, size(s));

        assert_true(pop(s, NULL)); // outValue can be NULL
        assert_equal_int(-1, s->top);
        assert_equal_int(0, size(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 7: peek without removing
    {
        printf("Test 7: peek without removing\n");
        Stack *s = create_stack();
        push(s, 55);
        push(s, 66);

        int value;
        assert_true(peek(s, &value));
        assert_equal_int(66, value);
        assert_equal_int(1, s->top); // top unchanged
        assert_equal_int(2, size(s)); // size unchanged

        assert_true(peek(s, NULL));
        assert_equal_int(2, size(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 8: is_empty and is_full basic checks
    {
        printf("Test 8: is_empty and is_full basic checks\n");
        Stack *s = create_stack();
        assert_true(is_empty(s));
        assert_false(is_full(s));

        // Fill to capacity
        for (size_t i = 0; i < INITIAL_CAPACITY; ++i)
            assert_true(push(s, (int)i));

        assert_false(is_empty(s));
        assert_true(is_full(s));
        assert_equal_int((int)INITIAL_CAPACITY - 1, s->top);

        delete_stack(&s);
        printf("\n");
    }

    // Test 9: resize_stack triggers on full
    {
        printf("Test 9: resize_stack triggers on full\n");
        Stack *s = create_stack();

        // Fill exactly to capacity
        for (size_t i = 0; i < INITIAL_CAPACITY; ++i)
            assert_true(push(s, (int)i));

        size_t old_capacity = s->capacity;
        assert_true(is_full(s));

        // Next push should trigger resize
        assert_true(push(s, 9999));
        assert_false(is_full(s));
        assert_equal_size_t(old_capacity * GROWTH_FACTOR, s->capacity);
        assert_equal_int((int)INITIAL_CAPACITY, s->top);
        assert_equal_int(9999, s->array[s->top]);

        int value;
        assert_true(peek(s, &value));
        assert_equal_int(9999, value);

        delete_stack(&s);
        printf("\n");
    }

    // Test 10: pop and peek on empty stack
    {
        printf("Test 10: pop and peek on empty stack\n");
        Stack *s = create_stack();
        int dummy;
        assert_false(pop(s, &dummy));
        assert_false(peek(s, &dummy));
        assert_true(is_empty(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 11: push/pop/peek on NULL stack
    {
        printf("Test 11: push/pop/peek on NULL stack\n");
        Stack *s = NULL;
        int dummy;

        assert_false(push(s, 999));
        assert_false(pop(s, &dummy));
        assert_false(peek(s, &dummy));
        assert_true(is_empty(s));
        assert_equal_int(0, size(s));

        printf("\n");
    }

    // Test 12: Full lifecycle with resize
    {
        printf("Test 12: Full lifecycle with resize\n");
        Stack *s = create_stack();

        // Push until resize occurs
        for (int i = 0; i < INITIAL_CAPACITY + 5; ++i)
            assert_true(push(s, i));

        // Verify top element
        int val;
        assert_true(peek(s, &val));
        assert_equal_int(INITIAL_CAPACITY + 4, val);

        // Pop a few
        for (int i = 0; i < 3; ++i) {
            assert_true(pop(s, &val));
            assert_equal_int(INITIAL_CAPACITY + 4 - i, val);
        }

        assert_equal_int(INITIAL_CAPACITY + 2, size(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 13: LIFO order verification after multiple operations
    {
        printf("Test 13: LIFO order verification after multiple operations\n");
        Stack *s = create_stack();

        push(s, 10);
        push(s, 20);
        push(s, 30);
        pop(s, NULL); // remove 30
        push(s, 40);
        push(s, 50);

        int vals[4];
        for (int i = 0; i < 4; ++i) {
            assert_true(pop(s, &vals[i]));
        }

        assert_equal_int(50, vals[0]);
        assert_equal_int(40, vals[1]);
        assert_equal_int(20, vals[2]);
        assert_equal_int(10, vals[3]);

        assert_true(is_empty(s));

        delete_stack(&s);
        printf("\n");
    }

    test_summary();

    return tests_failed;
}
