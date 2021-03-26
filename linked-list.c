#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

void List_Print(Node *head) {
  for (; head; head = head->next) {
    printf("%d\n", head->data);
  }
};

void List_Delete(Node **head, int n) {
  if (!(*head)) {
    return;
  }

  Node *ptr = *head;

  if (!n) {
    *head = ptr->next;
    free(ptr);

    return;
  }

  // [0]->[1]->[n]
  //       ^
  for (int i = 0; ptr && i < n - 1; i++) {
    ptr = ptr->next;
  }

  if (!ptr) {
    return;
  }

  // Node n
  Node *deleted = ptr->next;

  /*
   * [n-1]->[n]->[n+1]
   *
   * [n-1]->[n+1]; free([n])
   */
  ptr->next = deleted->next;
  free(deleted);
}

int Pop(Node **head) {
  int ret = (*head)->data;

  List_Delete(head, 0);
  return ret;
}

void List_Insert(Node **head, int data) {
  Node *new = malloc(sizeof *new);

  if (new) {
    new->data = data;
    new->next = *head;

    *head = new;
  }
}

void List_Reverse(Node **head) {
  if (!(*head)) {
    return;
  }

  Node *prev = (void *)0;

  for (Node *ptr = *head; ptr;) {
    Node *next = ptr->next;

    ptr->next = prev;
    prev = ptr;
    ptr = next;
  }

  *head = prev;
}

void List_Reverse_Recur(Node **head, Node *current) {
  if (!current->next) {
    *head = current;
    return;
  }

  List_Reverse_Recur(head, current->next);

  Node *prev = current->next;
  prev->next = current;
  current->next = (void *)0;
}

void List_Traverse(Node *head, void fn(int), _Bool rev) {
  if (!head) {
    return;
  }

  rev ? (fn(head->data), List_Traverse(head->next, fn, rev))
      : (List_Traverse(head->next, fn, rev), fn(head->data));
}

void print_node(int data) { printf("Node: %d\n", data); }

int main(int argc, const char *argv[argc]) {

  reverse_string("abc");

  return 0;
}
