#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct ListNode {
    int data;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

size_t get_length(const ListNode *head);

bool insert_first(ListNode **head, int data);

bool insert_last(ListNode **head, int data);

bool insert_at_position(ListNode **head, int data, size_t position);

bool delete_first(ListNode **head);

bool delete_last(ListNode **head);

bool delete_from_position(ListNode **head, size_t position);

void delete_list(ListNode **head);

#endif
