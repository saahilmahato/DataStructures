#include <stdlib.h>

#include "stack.h"

Stack *createStack() {
    Stack *stack = malloc(sizeof(*stack));
    if (stack)
        stack->top = NULL;

    return stack;
}

bool isEmpty(const Stack *stack) { return !stack || !stack->top; }

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
    if (!stack || isEmpty(stack))
        return false;

    ListNode *toDelete = stack->top;

    if (outValue)
        *outValue = toDelete->data;

    stack->top = toDelete->next;
    free(toDelete);

    return true;
}

bool peek(const Stack *stack, int *outValue) {
    if (!stack || isEmpty(stack))
        return false;

    if (outValue)
        *outValue = stack->top->data;

    return true;
}

void freeStack(Stack **stack) {
    if (stack && *stack) {
        while ((*stack)->top) {
            ListNode *toDelete = (*stack)->top;
            (*stack)->top = toDelete->next;
            free(toDelete);
        }

        free(*stack);
        *stack = NULL;
    }
}
