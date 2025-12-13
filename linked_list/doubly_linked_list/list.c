#include <stdlib.h>

#include "list.h"

size_t getLength(const ListNode *head) {
    size_t length = 0;
    while (head) {
        length++;
        head = head->next;
    }

    return length;
}

bool insertFirst(ListNode **head, const int data) {
    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;

    if (*head)
        (*head)->prev = newNode;

    *head = newNode;

    return true;
}

bool insertLast(ListNode **head, const int data) {
    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->next = NULL;

    if (!*head) {
        newNode->prev = NULL;
        *head = newNode;
        return true;
    }

    ListNode *current = *head;
    while (current->next)
        current = current->next;

    current->next = newNode;
    newNode->prev = current;

    return true;
}

bool insertAtPosition(ListNode **head, const int data, const size_t position) {
    if (position == 0)
        return insertFirst(head, data);

    if (!*head)
        return false;

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        if (!current->next)
            return false;

        current = current->next;
    }

    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->prev = current;
    newNode->next = current->next;
    current->next = newNode;

    if (newNode->next)
        newNode->next->prev = newNode;

    return true;
}

bool deleteFirst(ListNode **head) {
    if (!*head)
        return false;

    ListNode *toDelete = *head;
    *head = (*head)->next;

    if (*head)
        (*head)->prev = NULL;

    free(toDelete);

    return true;
}

bool deleteLast(ListNode **head) {
    if (!*head)
        return false;

    if (!(*head)->next) {
        free(*head);
        *head = NULL;
        return true;
    }

    ListNode *current = *head;
    while (current->next->next)
        current = current->next;

    free(current->next);
    current->next = NULL;

    return true;
}

bool deleteFromPosition(ListNode **head, const size_t position) {
    if (!*head)
        return false;

    if (position == 0)
        return deleteFirst(head);

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        if (!current->next)
            return false;

        current = current->next;
    }

    if (!current->next)
        return false;

    ListNode *toDelete = current->next;
    current->next = toDelete->next;

    if (toDelete->next)
        toDelete->next->prev = current;

    free(toDelete);

    return true;
}

void deleteList(ListNode **head) {
    while (*head) {
        ListNode *toDelete = *head;
        *head = (*head)->next;

        free(toDelete);
    }
}
