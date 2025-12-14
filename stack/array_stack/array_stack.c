#include <stdint.h>
#include <stdlib.h>

#include "array_stack.h"

Stack *create_stack() {
    Stack *stack = malloc(sizeof(*stack));
    if (!stack)
        return nullptr;

    stack->array = malloc(INITIAL_CAPACITY * sizeof(*stack->array));
    if (!stack->array) {
        free(stack);
        return nullptr;
    }

    stack->top = -1;
    stack->capacity = INITIAL_CAPACITY;

    return stack;
}

bool resize_stack(Stack *stack) {
    if (!stack || stack->capacity > SIZE_MAX / GROWTH_FACTOR)
        return false;

    const size_t newCapacity = stack->capacity * GROWTH_FACTOR;
    int *newArray = realloc(stack->array, newCapacity * sizeof(int));
    if (!newArray)
        return false;

    stack->array = newArray;
    stack->capacity = newCapacity;

    return true;
}

void delete_stack(Stack **stack) {
    if (stack && *stack) {
        free((*stack)->array);
        free(*stack);
        *stack = nullptr;
    }
}

bool is_empty(const Stack *stack) { return !stack || stack->top < 0; }

bool is_full(const Stack *stack) { return stack && stack->top == (int) stack->capacity - 1; }

bool push(Stack *stack, const int data) {
    if (!stack)
        return false;

    if (is_full(stack) && !resize_stack(stack))
        return false;

    stack->array[++stack->top] = data;
    return true;
}

bool pop(Stack *stack, int *outValue) {
    if (is_empty(stack))
        return false;

    if (outValue)
        *outValue = stack->array[stack->top];

    stack->top--;

    return true;
}

bool peek(const Stack *stack, int *outValue) {
    if (is_empty(stack))
        return false;

    if (outValue)
        *outValue = stack->array[stack->top];

    return true;
}

int size(const Stack *stack) { return stack ? stack->top + 1 : 0; }
