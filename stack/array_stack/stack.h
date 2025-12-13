#ifndef STACK_H
#define STACK_H

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

typedef struct {
    int top;
    size_t capacity;
    int *array;
} Stack;

Stack *createStack();

void destroy(Stack **stack);

bool resize(Stack *stack);

bool isEmpty(const Stack *stack);

bool isFull(const Stack *stack);

bool push(Stack *stack, int data);

bool pop(Stack *stack, int *outValue);

bool peek(const Stack *stack, int *outValue);

int size(const Stack *stack);

#endif
