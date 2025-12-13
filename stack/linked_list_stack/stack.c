#include <stdlib.h>

#include "stack.h"

Stack *create_stack() {
    Stack *stack = malloc(sizeof(*stack));
    if (stack)
        stack->top = nullptr;

    return stack;
}

void delete_stack(Stack **stack) {
    if (stack && *stack) {
        while ((*stack)->top) {
            ListNode *toDelete = (*stack)->top;
            (*stack)->top = toDelete->next;
            free(toDelete);
        }

        free(*stack);
        *stack = nullptr;
    }
}

bool is_empty(const Stack *stack) { return !stack || !stack->top; }

bool push(Stack *stack, const int data) {
    if (!stack)
        return false;

    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;

    return true;
}

bool pop(Stack *stack, int *outValue) {
    if (is_empty(stack))
        return false;

    ListNode *toDelete = stack->top;

    if (outValue)
        *outValue = toDelete->data;

    stack->top = toDelete->next;
    free(toDelete);

    return true;
}

bool peek(const Stack *stack, int *outValue) {
    if (is_empty(stack))
        return false;

    if (outValue)
        *outValue = stack->top->data;

    return true;
}
