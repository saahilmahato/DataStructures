#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stdbool.h>

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

typedef struct {
    int top;
    size_t capacity;
    int *array;
} Stack;

Stack *create_stack();

bool resize_stack(Stack *stack);

void delete_stack(Stack **stack);

bool is_empty(const Stack *stack);

bool is_full(const Stack *stack);

bool push(Stack *stack, int data);

bool pop(Stack *stack, int *outValue);

bool peek(const Stack *stack, int *outValue);

int size(const Stack *stack);

#endif
