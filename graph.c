#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
  unsigned int y;
  unsigned int weight;

  struct Edge *next; // next edge
} Edge;

typedef struct Graph {
  _Bool directed;
  unsigned int n;
  unsigned int m;
  unsigned int degree[100];

  Edge *edges[100];
} Graph;

typedef struct Queue {
  unsigned int back;
  unsigned int front;

  unsigned int vertices[100];
} Queue;

_Bool Empty(Queue *q) { return q->front == q->back; }

unsigned int Dequeue(Queue *q) {
  unsigned int vertex = q->vertices[q->front];
  q->vertices[q->front++] = 0;

  return vertex;
}
void Enqueue(Queue *q, unsigned int v) { q->vertices[q->back++] = v; }

void init_graph(Graph *g, _Bool directed) {
  g->directed = directed;

  for (size_t i = 1; i < 100; i++) {
    g->edges[i] = (void *)0;
    g->degree[i] = 0;
  }
}

void insert_edge(Graph *g, unsigned int x, unsigned int y, int weight) {
  Edge *e = malloc(sizeof *e);

  if (e) {
    e->y = y;
    e->weight = weight;
    e->next = g->edges[x]; // Current head or null
  }

  g->edges[x] = e; // Insert at head
  g->degree[x]++;

  g->n++;
}

// Insert Pair :: (Graph, Int, Int) -> Void
void insert_pair(Graph *g, unsigned int x, unsigned int y, int weight) {
  insert_edge(g, x, y, weight);
  if (!g->directed) {
    insert_edge(g, y, x, weight);
  }
}

void delete_edge(Graph *g, unsigned int x, unsigned int y) {
  Edge *cur = g->edges[x];

  g->degree[x]--;

  // If the head is Y
  if (cur->y == y) {
    cur = cur->next;
    free(cur);
    return;
  }

  // Advance until [prev]->[y]->[next]
  //                 ^
  while (cur->next && cur->next->y != y) {
    cur = cur->next;
  }

  Edge *delete = cur->next;

  cur->next = cur->next->next;

  free(delete);
}

void delete_list(Edge *e) {
  if (!e)
    return;

  delete_list(e->next);

  if (e) {
    free(e);
  }
}

void Delete(Graph *g) {
  for (size_t node = 0; node < 100; node++) {
    if (g->edges[node]) {
      delete_list(g->edges[node]);
    }
  }
}

void BFS(Graph *g, unsigned int start) {
  _Bool *explored = malloc(g->n * sizeof(_Bool));

  Queue q = {0};

  if (!explored) {
    return;
  }

  explored[start] = 1;

  Enqueue(&q, start);

  while (!Empty(&q)) {
    unsigned int v = Dequeue(&q);

    for (Edge *e = g->edges[v]; e; e = e->next) {
      if (!explored[e->y]) {
        explored[e->y] = 1;
        Enqueue(&q, e->y);
      }
    }
  }

  free(explored);
}

unsigned int ShortestPath(Graph *g, unsigned int start, unsigned int end) {
  if (start == end) {
    return 0;
  }

  unsigned int *explored = malloc(g->n * sizeof(unsigned int));
  memset(explored, 0, g->n * sizeof(unsigned int));

  Queue q = {0};

  if (!explored) {
    return 0;
  }

  explored[end] = 0;
  explored[start] = 1;

  Enqueue(&q, start);

  while (!Empty(&q)) {
    unsigned int v = Dequeue(&q);

    for (Edge *e = g->edges[v]; e; e = e->next) {
      if (!explored[e->y]) {
        explored[e->y] = explored[v] + 1;
        Enqueue(&q, e->y);
      }
    }
  }

  return explored[end] - 1;

  free(explored);

  return 0;
}

void explore(Graph *g, unsigned int start, _Bool explored[100]) {
  Queue q = {0};

  explored[start] = 1;

  Enqueue(&q, start);

  while (!Empty(&q)) {
    unsigned int v = Dequeue(&q);
    printf("Exploring Vertex(%d)\n", v);

    for (Edge *e = g->edges[v]; e; e = e->next) {
      if (!explored[e->y]) {
        explored[e->y] = 1;
        Enqueue(&q, e->y);
        printf("\tFound Vertex(%d)\n", e->y);
      }
    }
  }
}

void Connected(Graph *g) {
  _Bool *explored = malloc(100 * sizeof(_Bool));
  memset(explored, 0, 100 * sizeof(_Bool));

  for (size_t i = 0; i < g->n; i++) {
    if (g->edges[i] && !explored[i]) {
      explore(g, i, explored);
    }
  }

  free(explored);
}

void dfs_recur(Graph *g, unsigned int start, _Bool explored[]) {
  printf("Vertex %d\n", start);

  explored[start] = 1;

  for (Edge *e = g->edges[start]; e; e = e->next) {
    if (!explored[e->y]) {
      dfs_recur(g, e->y, explored);
    }
  }
}

void DFS(Graph *g, unsigned int start) {
  _Bool *explored = malloc(100 * sizeof(_Bool));
  memset(explored, 0, 100 * sizeof(_Bool));

  dfs_recur(g, start, explored);

  free(explored);
}

int Dijkstra(Graph *g, unsigned int start, unsigned int end) {
  int weights[100] = {0};
  weights[start] = 0;
  return 0;
}

int main() {
  Graph g = {0};
  init_graph(&g, 1);

  insert_pair(&g, 1, 2, 1);
  insert_pair(&g, 1, 3, 4);
  insert_pair(&g, 2, 3, 2);
  insert_pair(&g, 2, 4, 6);
  insert_pair(&g, 3, 4, 3);

  Connected(&g);

  Delete(&g);

  return 0;
}
