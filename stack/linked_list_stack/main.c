#include <stdio.h>
#include "../../test/test.h"
#include "linked_list_stack.h"

int main(void) {
    printf("Testing Linked List-Based Stack Implementation\n");
    printf("============================================\n\n");

    test_reset();

    // Test 1: create_stack basic creation
    {
        printf("Test 1: create_stack basic creation\n");
        Stack *s = create_stack();
        assert_not_null(s);
        assert_null(s->top);
        assert_true(is_empty(s));
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
        assert_not_null(s->top);
        assert_equal_int(42, s->top->data);
        assert_null(s->top->next);
        assert_false(is_empty(s));

        int value;
        assert_true(peek(s, &value));
        assert_equal_int(42, value);

        delete_stack(&s);
        printf("\n");
    }

    // Test 4: push multiple elements
    {
        printf("Test 4: push multiple elements\n");
        Stack *s = create_stack();
        assert_true(push(s, 10));
        assert_true(push(s, 20));
        assert_true(push(s, 30));

        assert_equal_int(30, s->top->data);
        assert_equal_int(20, s->top->next->data);
        assert_equal_int(10, s->top->next->next->data);
        assert_null(s->top->next->next->next);

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
        assert_null(s->top);
        assert_true(is_empty(s));

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
        assert_equal_int(20, s->top->data);

        assert_true(pop(s, &v2));
        assert_equal_int(20, v2);
        assert_equal_int(10, s->top->data);

        assert_true(pop(s, NULL)); // outValue can be NULL
        assert_null(s->top);
        assert_true(is_empty(s));

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
        assert_equal_int(66, s->top->data); // top unchanged
        assert_not_null(s->top->next);

        assert_true(peek(s, NULL));
        assert_equal_int(66, s->top->data);

        delete_stack(&s);
        printf("\n");
    }

    // Test 8: is_empty checks
    {
        printf("Test 8: is_empty checks\n");
        Stack *s = create_stack();
        assert_true(is_empty(s));

        push(s, 1);
        push(s, 2);
        assert_false(is_empty(s));

        pop(s, NULL);
        assert_false(is_empty(s));

        pop(s, NULL);
        assert_true(is_empty(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 9: pop on empty stack
    {
        printf("Test 9: pop on empty stack\n");
        Stack *s = create_stack();
        int dummy;
        assert_false(pop(s, &dummy));
        assert_null(s->top);
        assert_true(is_empty(s));

        delete_stack(&s);
        printf("\n");
    }

    // Test 10: peek on empty stack
    {
        printf("Test 10: peek on empty stack\n");
        Stack *s = create_stack();
        int dummy;
        assert_false(peek(s, &dummy));
        assert_null(s->top);

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

        printf("\n");
    }

    // Test 12: Full lifecycle - multiple operations
    {
        printf("Test 12: Full lifecycle - multiple operations\n");
        Stack *s = create_stack();

        assert_true(push(s, 100));
        assert_true(push(s, 200));
        assert_true(push(s, 300));

        int val;
        assert_true(peek(s, &val));
        assert_equal_int(300, val);

        assert_true(pop(s, &val));
        assert_equal_int(300, val);

        assert_true(push(s, 400));
        assert_true(peek(s, &val));
        assert_equal_int(400, val);

        assert_true(pop(s, NULL));
        assert_true(pop(s, NULL));
        assert_true(pop(s, NULL));
        assert_true(is_empty(s));

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
