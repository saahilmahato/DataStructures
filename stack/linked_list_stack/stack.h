#ifndef STACK_H
#define STACK_H

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct Stack {
    ListNode *top;
} Stack;

Stack *createStack();

bool isEmpty(const Stack *stack);

bool push(Stack *stack, int data);

bool pop(Stack *stack, int *outValue);

bool peek(const Stack *stack, int *outValue);

void freeStack(Stack **stack);

#endif
