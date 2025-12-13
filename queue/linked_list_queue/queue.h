#ifndef QUEUE_H
#define QUEUE_H

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct Queue {
    size_t size;
    ListNode *front;
    ListNode *rear;
} Queue;

Queue *createQueue(void);

void destroy(Queue **q);

bool enqueue(Queue *q, int value);

bool dequeue(Queue *q, int *out_value);

bool front(const Queue *q, int *out_value);

bool isEmpty(const Queue *q);

size_t size(const Queue *q);

#endif
