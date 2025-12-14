#ifndef LINKED_LIST_QUEUE_H
#define LINKED_LIST_QUEUE_H

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct Queue {
    size_t size;
    ListNode *front;
    ListNode *rear;
} Queue;

Queue *create_queue(void);

void delete_queue(Queue **q);

bool enqueue(Queue *q, int value);

bool dequeue(Queue *q, int *out_value);

bool front(const Queue *q, int *out_value);

bool is_empty(const Queue *q);

size_t size(const Queue *q);

#endif
