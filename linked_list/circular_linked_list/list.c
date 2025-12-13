#include <stdlib.h>

#include "list.h"

size_t getLength(ListNode *head) {
    size_t length = 0;

    if (!head)
        return length;

    const ListNode *current = head;
    do {
        length++;
        current = current->next;
    } while (current != head);

    return length;
}

bool insertFirst(ListNode **head, const int data) {
    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;

    if (!*head) {
        *head = newNode;
        newNode->next = newNode;
        return true;
    }

    ListNode *current = *head;
    while (current->next != *head)
        current = current->next;

    newNode->next = *head;
    current->next = newNode;
    *head = newNode;

    return true;
}

bool insertLast(ListNode **head, const int data) {
    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;

    if (!*head) {
        *head = newNode;
        newNode->next = newNode;
        return true;
    }

    ListNode *current = *head;
    while (current->next != *head)
        current = current->next;

    newNode->next = *head;
    current->next = newNode;

    return true;
}

bool insertAtPosition(ListNode **head, const int data, const size_t position) {
    if (position == 0)
        return insertFirst(head, data);

    if (!*head)
        return false;

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        current = current->next;
        if (current == *head)
            return false;
    }

    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->next = current->next;
    current->next = newNode;

    return true;
}

bool deleteFirst(ListNode **head) {
    if (!*head)
        return false;

    ListNode *toDelete = *head;

    if (toDelete->next == *head) {
        free(toDelete);
        *head = NULL;
        return true;
    }

    ListNode *current = *head;

    while (current->next != *head)
        current = current->next;

    *head = (*head)->next;
    current->next = *head;

    free(toDelete);

    return true;
}

bool deleteLast(ListNode **head) {
    if (!*head)
        return false;

    ListNode *current = *head;

    if (current->next == *head) {
        free(current);
        *head = NULL;
        return true;
    }

    while (current->next->next != *head)
        current = current->next;

    free(current->next);
    current->next = *head;

    return true;
}

bool deleteFromPosition(ListNode **head, const size_t position) {
    if (!*head)
        return false;

    if (position == 0)
        return deleteFirst(head);

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        current = current->next;
        if (current == *head)
            return false;
    }

    ListNode *toDelete = current->next;
    current->next = toDelete->next;

    free(toDelete);

    return true;
}

void deleteList(ListNode **head) {
    if (!*head)
        return;

    ListNode *current = *head;

    do {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    } while (current != *head);

    *head = NULL;
}
