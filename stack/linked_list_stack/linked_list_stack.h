#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct Stack {
    ListNode *top;
} Stack;

Stack *create_stack();

void delete_stack(Stack **stack);

bool is_empty(const Stack *stack);

bool push(Stack *stack, int data);

bool pop(Stack *stack, int *outValue);

bool peek(const Stack *stack, int *outValue);

#endif
