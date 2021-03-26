#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
  int data;

  struct DNode *prev;
  struct DNode *next;
} DNode;

void D_Print(DNode *head) {
  for (DNode *ptr = head; ptr; ptr = ptr->next) {
    printf("Data %d\n", ptr->data);
  }
}

void D_RPrint(DNode *head) {
  DNode *ptr = head;

  while (ptr) {
    ptr = ptr->next;
  }

  for (; ptr; ptr = ptr->prev) {
    printf("Data %d\n", ptr->data);
  }
}

void D_Insert_Head(DNode **head, int data) {

  DNode *new = malloc(sizeof *new);

  if (!new) {
    return;
  }

  new->data = data;
  new->prev = (void *)0;
  new->next = (void *)0;

  if (!(*head)) {
    *head = new;
    return;
  }

  (*head)->prev = new;
  new->next = *head;
  *head = new;
}

void D_Destroy(DNode *head) {
  if (!head) {
    return;
  }

  D_Destroy(head->next);
  free(head);
}

void D_Insert_Tail(DNode **head, int data) {
  DNode *new = malloc(sizeof *new);

  if (!new) {
    return;
  }

  new->data = data;
  new->prev = (void *)0;
  new->next = (void *)0;

  if (!(*head)) {
    *head = new;
    return;
  }

  DNode *tail = *head;
  while (tail->next) {
    tail = tail->next;
  }

  tail->next = new;
  new->prev = tail;
}

int main() {
  DNode *head = (void *)0;

  D_Insert_Head(&head, 3);
  D_Insert_Head(&head, 2);
  D_Insert_Head(&head, 1);

  D_Insert_Tail(&head, 4);
  D_Insert_Tail(&head, 5);
  D_Insert_Tail(&head, 6);

  D_Print(head);

  D_Destroy(head);

  return 0;
}
