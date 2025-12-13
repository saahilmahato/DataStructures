#include <stdlib.h>

#include "list.h"

size_t get_length(const ListNode *head) {
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

bool insert_first(ListNode **head, const int data) {
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

bool insert_last(ListNode **head, const int data) {
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

bool insert_at_position(ListNode **head, const int data, const size_t position) {
    if (position == 0)
        return insert_first(head, data);

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

bool delete_first(ListNode **head) {
    if (!*head)
        return false;

    ListNode *toDelete = *head;

    if (toDelete->next == *head) {
        free(toDelete);
        *head = nullptr;
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

bool delete_last(ListNode **head) {
    if (!*head)
        return false;

    ListNode *current = *head;

    if (current->next == *head) {
        free(current);
        *head = nullptr;
        return true;
    }

    while (current->next->next != *head)
        current = current->next;

    free(current->next);
    current->next = *head;

    return true;
}

bool delete_from_position(ListNode **head, const size_t position) {
    if (!*head)
        return false;

    if (position == 0)
        return delete_first(head);

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

void delete_list(ListNode **head) {
    if (!*head)
        return;

    ListNode *current = *head;
    do {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    } while (current != *head);

    *head = nullptr;
}
