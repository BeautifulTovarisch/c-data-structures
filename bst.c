#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key;

  struct Node *left;
  struct Node *right;
  struct Node *parent;
} Node;

Node *BST_Min(Node *node) {
  Node *cur = node;
  while (cur->left) {
    cur = cur->left;
  }

  return cur;
}

Node *BST_Max(Node *node) {
  Node *cur = node;
  while (cur->right) {
    cur = cur->right;
  }

  return cur;
}

Node *create_node(int key) {
  Node *new = malloc(sizeof *new);

  new->key = key;
  new->left = (void *)0;
  new->right = (void *)0;
  new->parent = (void *)0;

  return new;
}

void BST_Insert(Node **node, Node *parent, int key) {
  if (!(*node)) {
    *node = create_node(key);
    (*node)->parent = parent;
    return;
  }

  key < (*node)->key ? BST_Insert(&(*node)->left, *node, key)
                     : BST_Insert(&(*node)->right, *node, key);
}

void BST_Destroy(Node *node) {
  if (!node)
    return;

  BST_Destroy(node->left);
  BST_Destroy(node->right);

  if (node) {
    free(node);
  }

  node = (void *)0;
}

void BST_Traverse(Node *node) {
  if (!node)
    return;

  BST_Traverse(node->left);
  printf("Node(%d)\n", node->key);
  BST_Traverse(node->right);
}

Node *BST_Search(Node *node, int key) {
  if (!node) {
    return (void *)0;
  }

  if (node->key == key) {
    return node;
  }

  return key < node->key ? BST_Search(node->left, key)
                         : BST_Search(node->right, key);
}

Node *BST_Predecessor(Node *node, int key) {
  if (!node) {
    return (void *)0;
  }

  Node *n = BST_Search(node, key);

  if (n && n->left) {
    return BST_Max(n->left);
  }

  for (Node *cur = n; cur->parent; cur = cur->parent) {
    if (cur->parent->key < n->key) {
      return cur->parent;
    }
  }

  return (void *)0;
}

Node *BST_Successor(Node *node, int key) {
  if (!node) {
    return (void *)0;
  }

  Node *n = BST_Search(node, key);

  if (n && n->right) {
    return BST_Min(n->right);
  }

  for (Node *cur = n; cur->parent; cur = cur->parent) {
    if (cur->parent->key > n->key) {
      return cur->parent;
    }
  }

  return (void *)0;
}

void BST_Delete(Node *root, int key) {
  Node *delete = BST_Search(root, key);

  if (!delete) {
    return;
  }

  if (!delete->left && !delete->right) {
    if (delete->parent) {
      delete->key < delete->parent->key && (delete->parent->left = (void *)0);
      delete->key > delete->parent->key && (delete->parent->right = (void *)0);
    }

    free(delete);

    delete = (void *)0;

    return;
  }

  if (delete->left && delete->right) {

    Node *pred = BST_Predecessor(root, key);

    // Swap(pred(k), k);
    int temp = pred->key;
    pred->key = delete->key;
    delete->key = temp;

    BST_Delete(root, key);
  }

  if (delete->left) {
    delete->key < delete->parent->key ? (delete->parent->left = delete->left)
                                      : (delete->parent->right = delete->left);
    free(delete);
    delete = (void *)0;
    return;
  }

  if (delete->right) {
    delete->key < delete->parent->key ? (delete->parent->left = delete->right)
                                      : (delete->parent->right = delete->right);

    free(delete);
    delete = (void *)0;

    return;
  }
}

int main() {
  Node *root = (void *)0;

  for (int i = 0; i < 10; i++) {
    BST_Insert(&root, root, rand() % 100);
  }

  printf("(Min, Max) = (%d, %d)\n", BST_Min(root)->key, BST_Max(root)->key);

  int query = 77;
  Node *pred = BST_Predecessor(root, query);
  Node *succ = BST_Successor(root, query);

  if (pred) {
    printf("Predecessor(%d) == %d\n", query, pred->key);
  }

  if (succ) {
    printf("Successor(%d) == %d\n", query, succ->key);
  }

  int delete = 49;
  printf("Deleting %d\n", delete);

  BST_Delete(root, delete);

  BST_Traverse(root);

  BST_Destroy(root);
}
