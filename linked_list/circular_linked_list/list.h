#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

size_t getLength(ListNode *head);

bool insertFirst(ListNode **head, int data);

bool insertLast(ListNode **head, int data);

bool insertAtPosition(ListNode **head, int data, size_t position);

bool deleteFirst(ListNode **head);

bool deleteLast(ListNode **head);

bool deleteFromPosition(ListNode **head, size_t position);

void deleteList(ListNode **head);

#endif
